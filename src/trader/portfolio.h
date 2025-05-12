/**
 * @file portfolio.h
 * @brief Portfolio management for tracking stock positions and performance
 * 
 * This file defines the Portfolio class and StockInfo struct which manage
 * stock positions, track performance metrics, and maintain trading history.
 */

#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <cmath>

#include "../market/stock_data.h"

/**
 * @struct StockInfo
 * @brief Structure holding information about a stock position
 * 
 * Tracks various metrics for a stock position including quantity,
 * current price, market value, cost basis, and gain/loss.
 */
struct StockInfo {
    std::string symbol;      ///< Stock symbol
    int quantity;           ///< Number of shares owned
    double current_stock_price;  ///< Current price per share
    double market_value;    ///< Total market value of position
    double cost_basis;      ///< Average cost per share
    double gain_or_loss;    ///< Current unrealized gain/loss
    std::queue<std::pair<double, int>> shares;  ///< Queue of share purchases with prices

    /**
     * @brief Constructs a new StockInfo instance
     */
    StockInfo();

    /**
     * @brief Updates position information after a buy
     * 
     * @param price Price per share
     * @param q Quantity of shares
     */
    void updateBuy(double price, int q);

    /**
     * @brief Updates position information after a sell
     * 
     * @param price Price per share
     * @param q Quantity of shares
     */
    void updateSell(double price, int q);

    /**
     * @brief Updates market value and gain/loss based on current price
     * 
     * @param closingPrice Current market price
     */
    void updateVals(double closingPrice);
};

/**
 * @class Portfolio
 * @brief Manages a collection of stock positions and trading history
 * 
 * The Portfolio class provides functionality to:
 * - Add and remove stock positions
 * - Track position performance
 * - Maintain trading history
 * - Generate performance reports
 */
class Portfolio {
  public:
    /**
     * @brief Constructs a new Portfolio instance
     */
    Portfolio();

    /**
     * @brief Adds a stock position to the portfolio
     * 
     * @param price Price per share
     * @param quantity Number of shares to add
     */
    void addStock(double price, int quantity);

    /**
     * @brief Removes a stock position from the portfolio
     * 
     * @param price Price per share
     * @param quantity Number of shares to remove
     */
    void removeStock(double price, int quantity);

    /**
     * @brief Gets the total number of stocks in the portfolio
     * 
     * @return Number of stocks
     */
    int getNumberOfStock();

    /**
     * @brief Prints portfolio performance information
     * 
     * @param closing Current closing price
     * @param y Years of trading history
     * @param type Type of information to print
     * @param history Whether to include trading history
     */
    void print(double closing, double y, std::string type, bool history);

  private:
    StockInfo info;  ///< Information about the current stock position
    std::vector<std::pair<std::string, double>> stockHistory;  ///< History of stock prices
};