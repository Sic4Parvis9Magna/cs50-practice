import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from constants import *
from sql_util import *

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
# db = SQL(DB_URL)

# Make sure API key is set
# if not os.environ.get("API_KEY"):
#     raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    #TBD
    portfolio_cash = 0.0
    user_id = session['user_id']
    results = get_portfolios(user_id)
    if len(results) != 0:
        for result in results:
            symbol = result['stockname']
            stock_info = lookup(symbol)
            if stock_info:
                price_str = stock_info['price']
                result['price'] = usd(stock_info['price'])
                cost = int(result['amount']) * float(price_str)
                portfolio_cash += cost
                result['holding'] = usd(cost)

    user = get_user_by_id(user_id)[0]
    cash = float(user['cash'])
    balance = {
        'cash': usd(cash),
        'stocks': usd(portfolio_cash),
        'total': usd(cash + portfolio_cash)
    }

    return render_template(HOME_PAGE, session=SESSION_TRUE, results=results, balance=balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        
        symbol = request.form.get('symbol')
        if not symbol:
            error = {'message': 'stock symbol should be provided'}
            return render_template(BUY_PAGE, error=error)
        
        shares = request.form.get('shares')
        if not shares or not shares.isdigit() or int(shares) < 0:
            error = {'message': 'stock shares number should be provided and it should be a positive integer!'}
            return render_template(BUY_PAGE, error=error)
        
        result = lookup(symbol)
        if not result:
            error = {'message': 'provided stock symbol not found on the market'}
            return render_template(BUY_PAGE, error=error)
        
        total_cost = int(shares) * float(result['price'])
        user_id = session['user_id']
        rows = get_user_by_id(user_id=user_id)
        #TODO fink about handling errors here
        money = float(rows[0]['cash'])

        if total_cost > money:
            error = {'message': 'Not enough money to buy this stocks package'}
            return render_template(BUY_PAGE, error=error)
        
        money_left = money - total_cost

        # update money
        update_cash(user_id=user_id, cash=money_left)

        # create/update portfolios
        company = result['name']
        rows = get_portfolio_by_stockinfo(usr_id=user_id, stockname=symbol, company=company)

        if len(rows) == 1:
            portfolion_id = rows[0]['id']
            old_amount = rows[0]['amount']
            total_amount = int(old_amount) + int(shares)
            update_portfolio(portfolio_id=portfolion_id, amount=total_amount)
        else:
            add_portfolio(usr_id=user_id, stockname=symbol, amount=shares, company=company)

        # update history
        add_history(usr_id=user_id, stockname=symbol, amount=shares, price=result['price'],
        company=company, operation='buy')

        bought = {'number': shares,'stock': symbol}
        return render_template(BUY_PAGE, bought=bought)

    else:
        return render_template(BUY_PAGE)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    histories = get_histories(session['user_id'])
    return render_template(HISTORY_PAGE, histories=histories)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        username = request.form.get("username")
        pwd = request.form.get("password") 
        if not username:
            return apology("must provide username", BAD_REQUEST)

        # Ensure password was submitted
        if not pwd:
            return apology("must provide password", BAD_REQUEST)

        # Query database for username
        rows = get_user_by_name(username)

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], pwd):
            return apology("invalid username and/or password", BAD_REQUEST)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template(LOGIN_PAGE)


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return render_template(LOGIN_PAGE, logout=True)


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
     # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("You mast provide stock name!", BAD_REQUEST)
        result = lookup(symbol)
        result['price'] = usd(result['price'])

        return render_template(QUOTED_PAGE, symbol=symbol, result=result)
    else:    
        return render_template(QUOTE_PAGE, session=SESSION_TRUE)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
     # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
    # User reached route via GET (as by clicking a link or via redirect)
        username = request.form.get("username")
        pwd = request.form.get("password")
        confrimation = request.form.get("confrimation") 
        # Ensure username was submitted
        if not username:
            return apology("must provide username", BAD_REQUEST)

        # Ensure password was submitted
        elif not pwd:
            return apology("must provide password", BAD_REQUEST)
        
        # Ensure confrimation was submitted
        elif not confrimation:
            return apology("must provide confrimation", BAD_REQUEST)
        
        #check if pwd and confrimation are equals
        elif not pwd == confrimation:
            return apology("must provide confrimation should be equal to password", BAD_REQUEST)

        else:
            # Query database for username
            rows = get_user_by_name(username)

            # Check if username exists
            if len(rows) != 0:
                return apology("Sorry this username already in use please choose another username", BAD_REQUEST)
            
            hash_value = generate_password_hash(pwd)
            add_user(username, hash_value)

            return redirect("/")
    else:
        return render_template(REGISTER_PAGE)



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session['user_id']
    if request.method == "POST":
        
        symbol = request.form.get("stockname")
        if not symbol:
            error = {"message": "Stock symbol not found!"}
            return render_template(SELL_PAGE, session=SESSION_TRUE, error=error, results=form_sell_table(user_id))
        
        stock_info = lookup(symbol)
        if not stock_info:
            error = {"message": "Stock symbol not found on the market!"}
            return render_template(SELL_PAGE, session=SESSION_TRUE, error=error, results=form_sell_table(user_id))

        amount_to_sell = request.form.get("number")
        if not amount_to_sell or not amount_to_sell.isdigit() or int(amount_to_sell) < 0:
            error = {"message": "You should provide positive integer amound of stocks to sell!"}
            return render_template(SELL_PAGE, session=SESSION_TRUE, error=error, results=form_sell_table(user_id))
        
        company = request.form.get("company")
        if not company:
            error = {"message": "Company name not found!"}
            return render_template(SELL_PAGE, session=SESSION_TRUE, error=error, results=form_sell_table(user_id))
        
        rows = get_portfolio_by_stockinfo(usr_id=session['user_id'], stockname=symbol, company=company) 
        if len(rows) != 1:
            error = {"message": "Ups you have not brought that stock yet"}
            return render_template(SELL_PAGE, session=SESSION_TRUE, error=error, results=form_sell_table(user_id))
        
        old_amount = int(rows[0]['amount'])

        if old_amount < int(amount_to_sell):
            error = {"message": "Ups you have not enough shares!"}
            return render_template(SELL_PAGE, session=SESSION_TRUE, error=error, results=form_sell_table(user_id))

        benefit = int(amount_to_sell) * float(stock_info['price'])
        #update porfolio
        new_amount = int(old_amount) - int(amount_to_sell)
        update_portfolio_by_name(usr_id=user_id, stockname=symbol, company=company, amount=new_amount)
        
        #update cash
        rows = get_user_by_id(user_id=user_id)
        updated_cash = float(rows[0]['cash']) + benefit 
        update_cash(user_id=user_id, cash=updated_cash)

        #update history
        add_history(usr_id=user_id, stockname=symbol, amount=amount_to_sell, price=stock_info['price'],
        company=company, operation='sell')

        success={
            'message': f'An old amount is {old_amount}\nYou successfully selled {symbol} of {company} in amount of {int(amount_to_sell)} and gain {usd(benefit)}!'
        }
        return render_template(SELL_PAGE, session=SESSION_TRUE, results=form_sell_table(user_id), success=success)
    else:
        return render_template(SELL_PAGE, session=SESSION_TRUE, results=form_sell_table(user_id))


def form_sell_table(user_id):
    results = get_portfolios(user_id)
    if len(results) != 0:
        for result in results:
            symbol = result['stockname']
            stock_info = lookup(symbol)
            if stock_info:
                price_str = stock_info['price']
                result['price'] = usd(stock_info['price'])
    ## TODO add 'index' like cash info
    return results


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
