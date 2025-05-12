/**
 * @file stock_market.h
 * @brief Stock market simulation and data management
 * 
 * This file defines the StockMarket class which manages stock data,
 * simulates market behavior, and notifies traders of price changes.
 */

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

/**
 * @class StockMarket
 * @brief Manages stock market simulation and trader notifications
 * 
 * The StockMarket class:
 * - Loads historical stock data from SQLite database
 * - Manages a list of traders to notify of price changes
 * - Runs market simulations over specified date ranges
 * - Provides real-time price updates to traders
 */
class StockMarket {
  public:
    /**
     * @brief Constructs a new StockMarket instance
     * 
     * @param symbol Stock symbol to track
     * @param start Start date for simulation
     * @param end End date for simulation
     */
    StockMarket(std::string symbol, std::string start, std::string end);

    /**
     * @brief Adds a trader to receive price updates
     * 
     * @param trader Pointer to the trader to add
     */
    void addTrader(Trader *trader);

    /**
     * @brief Notifies all traders of a price change
     * 
     * @param newPrice The new stock price
     */
    void notifyTraders(double newPrice);

    /**
     * @brief Runs the market simulation
     * 
     * Iterates through historical data and notifies traders
     * of price changes at each time step.
     */
    void runSimulation();

  private:
    std::vector<Trader*> traders;  ///< List of traders to notify

    std::string stock_symbol;  ///< Stock symbol being tracked
    std::string start_date;    ///< Simulation start date
    std::string end_date;      ///< Simulation end date
    std::string current_date;  ///< Current simulation date
    
    /**
     * @brief Sets up the SQLite database connection
     */
    void setDataBase();

    /**
     * @brief Connects to the stock data table
     */
    void connectDataTable();

    /**
     * @brief Retrieves new stock data from the database
     */
    void getNewStockData();

    sqlite3 *db;           ///< SQLite database connection
    sqlite3_stmt *stmt;    ///< SQLite prepared statement
    std::string datatable; ///< Name of the data table
    int rc;               ///< SQLite return code
};