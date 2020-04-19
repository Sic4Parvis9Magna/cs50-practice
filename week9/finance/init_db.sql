CREATE TABLE IF NOT EXISTS 'users' (
    'id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    'username' TEXT NOT NULL,
    'hash' TEXT NOT NULL,
    'cash' NUMERIC NOT NULL DEFAULT 10000.00
);
CREATE TABLE IF NOT EXISTS 'portfolios' (
    'id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    'usr_id' INTEGER NOT NULL,
    'stockname' TEXT NOT NULL,
    'amount' INTEGER NOT NULL DEFAULT 0,
    'company' TEXT NOT NULL,
    FOREIGN KEY(usr_id) REFERENCES users(id) 
);
CREATE TABLE IF NOT EXISTS 'histories' (
    'id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    'usr_id' INTEGER NOT NULL,
    'stockname' TEXT NOT NULL,
    'amount' INTEGER NOT NULL,
    'price' NUMERIC NOT NULL,
    'company' TEXT NOT NULL ,
    'operation' TEXT NOT NULL,
    'timestamp' TEXT NOT NULL,
    FOREIGN KEY(usr_id) REFERENCES users(id) 
);
CREATE UNIQUE INDEX IF NOT EXISTS 'username' ON "users" ("username");

-- CREATE TABLE IF NOT EXISTS sqlite_sequence(name,seq);
-- CREATE UNIQUE INDEX IF NOT EXISTS 'portfolio' ON "portfolios" ("usr_id");
-- CREATE UNIQUE INDEX IF NOT EXISTS 'history' ON "histories" ("usr_id");