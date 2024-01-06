import yfinance as yf
import sqlite3
from datetime import datetime

def fetch_and_store_stock_data(symbol, start_date, end_date, database_path='stock_data.db'):
    # Fetch stock data from Yahoo Finance
    stock_data = yf.download(symbol, start=start_date, end=end_date)

    # Connect to SQLite database
    conn = sqlite3.connect(database_path)
    cursor = conn.cursor()

    # Drop existing tables
    cursor.execute('PRAGMA foreign_keys=off;')
    cursor.execute('BEGIN TRANSACTION;')
    cursor.execute('DROP TABLE IF EXISTS stock_data;')
    cursor.execute('COMMIT;')
    cursor.execute('PRAGMA foreign_keys=on;')

    # Create a table
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS stock_data (
            symbol TEXT,
            date TEXT PRIMARY KEY,
            open REAL,
            high REAL,
            low REAL,
            close REAL,
            volume INTEGER
        )
    ''')

    # Insert stock data into the database
    for index, row in stock_data.iterrows():
        date_str = index.strftime('%Y-%m-%d')
        cursor.execute('''
            INSERT INTO stock_data
            VALUES (?, ?, ?, ?, ?, ?, ?)
        ''', (symbol, date_str, row['Open'], row['High'], row['Low'], row['Close'], row['Volume']))

    # Commit changes and close the connection
    conn.commit()
    conn.close()
