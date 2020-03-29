import sys
from cs50 import SQL

db_addres = "sqlite:///students.db"
SELECT_SQL_STATEMENT = 'SELECT * FROM students WHERE house = ? ORDER BY last, first'

def main():
    args = sys.argv
    if len(args) != 2:
        print("Wrong args number. \nExample: python roster.py Gryffindor")
        exit(1)
   
    db = SQL(db_addres)
    rows = db.execute(SELECT_SQL_STATEMENT, args[1])
    for row in rows:
        first = row['first']
        middle = row['middle'] 
        if middle == 'NULL':
            middle = ' '
        else:
            middle = ' {} '.format(middle)
        last = row['last']
        birth = row['birth']

        print(f"{first}{middle}{last}, born {birth}")
    
main()