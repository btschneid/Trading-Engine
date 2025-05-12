/**
 * @file stock_data.h
 * @brief Stock data structure and utilities
 * 
 * This file defines the StockData struct which represents
 * a single data point for a stock, including its symbol,
 * date, and closing price.
 */

#ifndef STOCK_DATA_H
#define STOCK_DATA_H

#include <iostream>
#include <string>

/**
 * @struct StockData
 * @brief Structure representing a single stock data point
 * 
 * Contains the essential information for a stock at a given point in time:
 * - Stock symbol
 * - Date
 * - Closing price
 */
struct StockData {
    std::string symbol;  ///< Stock symbol (e.g., "AAPL")
    std::string date;    ///< Date of the data point
    double close;        ///< Closing price for the day

    /**
     * @brief Default constructor
     * 
     * Initializes a StockData instance with empty symbol and date,
     * and zero closing price.
     */
    StockData();

    /**
     * @brief Parameterized constructor
     * 
     * @param _symbol Stock symbol
     * @param _date Date of the data point
     * @param _close Closing price
     */
    StockData(std::string _symbol, std::string _date, double _close);
};

#endif // STOCK_DATA_H