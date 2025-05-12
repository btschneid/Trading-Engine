import yfinance as yf
import sqlite3
from datetime import datetime

def fetch_and_store_stock_data(symbol, start_date, end_date, database_path='stock_data.db'):
    # Connect to SQLite database
    conn = sqlite3.connect(database_path)
    cursor = conn.cursor()

    # Create table if it doesn't exist
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

    # Check if we already have the requested data
    cursor.execute('''
        SELECT COUNT(*) FROM stock_data 
        WHERE symbol = ? AND date BETWEEN ? AND ?
    ''', (symbol, start_date, end_date))
    
    existing_count = cursor.fetchone()[0]
    
    # If we have all the data, no need to download
    if existing_count > 0:
        print(f"Found existing data for {symbol} from {start_date} to {end_date}")
        conn.close()
        return True

    print(f"Downloading data for {symbol} from {start_date} to {end_date}")
    # Fetch stock data from Yahoo Finance
    stock_data = yf.download(symbol, start=start_date, end=end_date)

    # Begin transaction
    cursor.execute('BEGIN TRANSACTION')

    try:
        # Insert or replace stock data into the database
        for index, row in stock_data.iterrows():
            date_str = index.strftime('%Y-%m-%d')
            cursor.execute('''
                INSERT OR REPLACE INTO stock_data
                VALUES (?, ?, ?, ?, ?, ?, ?)
            ''', (
                symbol,
                date_str,
                float(row['Open'].iloc[0]),
                float(row['High'].iloc[0]),
                float(row['Low'].iloc[0]),
                float(row['Close'].iloc[0]),
                int(row['Volume'].iloc[0])
            ))

        # Commit the transaction
        conn.commit()
        print(f"Successfully stored data for {symbol}")
    except Exception as e:
        # Rollback in case of error
        conn.rollback()
        print(f"Error storing data: {str(e)}")
        return False
    finally:
        conn.close()

    return True
