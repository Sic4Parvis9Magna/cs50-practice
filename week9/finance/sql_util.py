import datetime

from cs50 import SQL

DB_URL = "sqlite:///finance.db"

# users
SQL_GET_USER_BY_NAME = "SELECT id, username, hash, cash FROM users WHERE username = :username"
SQL_GET_USER_BY_ID = "SELECT id, username, hash, cash FROM users WHERE id = :user_id"
SQL_INSERT_NEW_USER = "INSERT INTO users (username, hash) VALUES(:username, :hash_value)"
SQL_UPDATE_CASH = "UPDATE users SET cash=:cash WHERE id = :user_id"

# Portfolio
SQL_GET_PORTFOLIO_BY_STOCKINFO = """
SELECT id, amount FROM portfolios WHERE usr_id = :usr_id AND stockname = :stockname AND company = :company"""
SQL_INSERT_NEW_PORTFOLIO = """
INSERT INTO portfolios (usr_id, stockname, amount, company) VALUES(:usr_id, :stockname, :amount, :company)"""
SQL_UPDATE_PORTFOLIO_AMOUNT = "UPDATE portfolios SET amount=:amount WHERE id = :portfolio_id"
SQL_UPDATE_PORTFOLIO_AMOUNT_BY_NAME = """
UPDATE portfolios SET amount=:amount
WHERE usr_id = :usr_id AND stockname = :stockname AND company = :company"""
SQL_GET_USER_PORTFOLIOS = "SELECT stockname, amount, company FROM portfolios WHERE usr_id = :usr_id"

# History
SQL_INSERT_NEW_HISTORY = """
INSERT INTO 
histories (usr_id, stockname, amount, price, company, operation, timestamp)
VALUES(:usr_id, :stockname, :amount, :price, :company, :operation, :timestamp)
"""
SQL_GET_HISTORIES = """
SELECT stockname, amount, price, company, operation, timestamp FROM histories
WHERE usr_id = :usr_id
"""
# intersections

# functions
# users
def get_user_by_name(username):
    db = SQL(DB_URL)
    return db.execute(SQL_GET_USER_BY_NAME, username=username)

def add_user(username, hash_value):
    db = SQL(DB_URL)
    db.execute(SQL_INSERT_NEW_USER, username=username, hash_value=hash_value)

def get_user_by_id(user_id):
    db = SQL(DB_URL)
    return db.execute(SQL_GET_USER_BY_ID, user_id=user_id)

def update_cash(user_id, cash):
    db = SQL(DB_URL)
    return db.execute(SQL_UPDATE_CASH, user_id=user_id, cash=cash)

# Portfolio
def get_portfolio_by_stockinfo(usr_id, stockname, company):
    db = SQL(DB_URL)
    return db.execute(SQL_GET_PORTFOLIO_BY_STOCKINFO, usr_id=usr_id, stockname=stockname, company=company)

def add_portfolio(usr_id, stockname, amount, company):
    db = SQL(DB_URL)
    return db.execute(SQL_INSERT_NEW_PORTFOLIO, usr_id=usr_id, stockname=stockname, amount=amount, company=company)

def update_portfolio(portfolio_id, amount):
    db = SQL(DB_URL)
    return db.execute(SQL_UPDATE_PORTFOLIO_AMOUNT, portfolio_id=portfolio_id, amount=amount)

def update_portfolio_by_name(usr_id, stockname, company, amount):
    db = SQL(DB_URL)
    return db.execute(SQL_UPDATE_PORTFOLIO_AMOUNT_BY_NAME, usr_id=usr_id, stockname=stockname, company=company, amount=amount)

def get_portfolios(usr_id):
    db = SQL(DB_URL)
    return db.execute(SQL_GET_USER_PORTFOLIOS, usr_id=usr_id)


#history
def add_history(usr_id, stockname, amount, price, company, operation):
    db = SQL(DB_URL)
    timestamp = datetime.datetime.utcnow()
    return db.execute(SQL_INSERT_NEW_HISTORY,
     usr_id=usr_id, stockname=stockname, amount=amount,
     price=price, company=company, operation=operation, timestamp=timestamp)

def get_histories(usr_id):
    db = SQL(DB_URL)
    return db.execute(SQL_GET_HISTORIES, usr_id=usr_id)