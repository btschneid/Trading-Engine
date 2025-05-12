#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>

#include "sqlite3.h"
#include "stock_data.h"
#include "../trader/trader.h"


class StockMarket {
  public:

    StockMarket(std::string symbol, std::string start, std::string end);

    void addTrader(Trader *trader);
    void notifyTraders(double newPrice);

    void runSimulation();

  private:
    std::vector<Trader*> traders;

    std::string stock_symbol;
    std::string start_date;
    std::string end_date;
    std::string current_date;
    
    void setDataBase();
    void connectDataTable();
    void getNewStockData();

    sqlite3 *db;
    sqlite3_stmt *stmt;
    std::string datatable;
    int rc;
};