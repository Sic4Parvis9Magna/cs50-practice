import csv
import sys
from cs50 import SQL

db_addres = "sqlite:///students.db"
name_key = 'name'
house_key = 'house'
birth_key = 'birth'
ISERT_SQL_STATEMENT = 'INSERT INTO students(first, middle, last, house, birth) VALUES(?,?,?,?,?)'

def main():
    args = sys.argv
    if len(args) != 2:
        print("Wrong args number. \nExample: python import.py [file.csv]")
        exit(1)
   
    db = SQL(db_addres)
    with open(args[1], "r") as input_data:
        reader = csv.DictReader(input_data)
        for row in reader:
            name_parts = row[name_key].split()
            first = name_parts[0]
            if len(name_parts) > 2:
                mid = name_parts[1]
                last = name_parts[2]
            else:
                mid = 'NULL'
                last = name_parts[1]
            house = row[house_key]
            birth = int(row[birth_key])
            db.execute(ISERT_SQL_STATEMENT,first, mid, last, house, birth)
main()
