#include "sqlite3.h"
#include "stock_market.h"
#include "stock_data.h"
#include "../Trader/trader.h"

StockMarket::StockMarket(std::string symbol, std::string start, std::string end)
: stock_symbol(symbol), start_date(start), end_date(end), current_date(start) {

  // Connect to the database
  setDataBase();
}

void StockMarket::addTrader(Trader *trader) {
  traders.push_back(trader);
}

// Notify traders of new stock data
void StockMarket::notifyTraders(double newPrice) {
  for (Trader* trader : traders) {
    trader->notify(newPrice);
  }
}

void StockMarket::runSimulation() {
  // Connect to the datatable
  connectDataTable();
  sqlite3_finalize(stmt);
  sqlite3_close(db);
}

void StockMarket::setDataBase() {
  rc = sqlite3_open("./stock_data.db", &db);

  if (rc) {
    std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << "\n";
    return;
  }

  std::cout << "Connected to database\n";
}

void StockMarket::connectDataTable() {
  std::cout << std::fixed << std::setprecision(2);
  
  // Construct the SELECT query
  std::string query = "SELECT date, close FROM stock_data;";

  rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

  if (rc == SQLITE_OK) {
    getNewStockData();
  } else {
    std::cerr << "Cannot execute query: " << sqlite3_errmsg(db) << "\n";
  }
}

void StockMarket::getNewStockData() {
  std::cout << "Simulating " << stock_symbol << "!\n";

  // Step through each row in the result set
  while (true) {

    if (sqlite3_step(stmt) != SQLITE_ROW) {
      break;
    }

    // Print each column in the current row
    for (int i = 0; i < sqlite3_column_count(stmt); ++i) {
      const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
      if (i == 1) {
        notifyTraders(std::atof(value));
      }
    }
  }
    
}