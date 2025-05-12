#include "sqlite3.h"
#include "stock_market.h"
#include "stock_data.h"
#include "../trader/trader.h"

// Initialize market with symbol and date range, then connect to database
StockMarket::StockMarket(std::string symbol, std::string start, std::string end)
: stock_symbol(symbol), start_date(start), end_date(end), current_date(start) {
  setDataBase();
}

void StockMarket::addTrader(Trader *trader) {
  traders.push_back(trader);
}

// Notify all registered traders of price changes
void StockMarket::notifyTraders(double newPrice) {
  for (Trader* trader : traders) {
    trader->notify(newPrice);
  }
}

// Connect to database, process data, and clean up resources
void StockMarket::runSimulation() {
  connectDataTable();
  sqlite3_finalize(stmt);
  sqlite3_close(db);
}

// Open connection to SQLite database and handle errors
void StockMarket::setDataBase() {
  rc = sqlite3_open("./data/stock_data.db", &db);

  if (rc) {
    std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << "\n";
    return;
  }

  std::cout << "Connected to database\n";
}

// Prepare SQL query to retrieve date and closing price data
void StockMarket::connectDataTable() {
  std::cout << std::fixed << std::setprecision(2);
  
  std::string query = "SELECT date, close FROM stock_data;";

  rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

  if (rc == SQLITE_OK) {
    getNewStockData();
  } else {
    std::cerr << "Cannot execute query: " << sqlite3_errmsg(db) << "\n";
  }
}

// Process each row of stock data and notify traders of price changes
void StockMarket::getNewStockData() {
  std::cout << "Simulating " << stock_symbol << "!\n";

  while (true) {
    if (sqlite3_step(stmt) != SQLITE_ROW) {
      break;
    }

    for (int i = 0; i < sqlite3_column_count(stmt); ++i) {
      const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
      if (i == 1) {
        notifyTraders(std::atof(value));
      }
    }
  }
}