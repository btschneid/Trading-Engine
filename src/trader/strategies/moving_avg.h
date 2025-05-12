/**
 * @file moving_avg.h
 * @brief Moving average trading strategy implementation
 * 
 * This file defines the MovingAverage class which implements a trading
 * strategy based on Simple Moving Averages (SMA). It uses two SMAs of
 * different periods to generate buy/sell signals.
 */

#pragma once

#include <iostream>
#include <deque>
#include <limits>

#include "../trader.h"

/**
 * @struct SMA
 * @brief Structure holding Simple Moving Average data
 * 
 * Contains price and SMA values for both short and long periods
 * at a given point in time.
 */
struct SMA {
    double price;      ///< Current price
    double sma_short;  ///< Short-period SMA value
    double sma_long;   ///< Long-period SMA value

    /**
     * @brief Default constructor
     */
    SMA();

    /**
     * @brief Parameterized constructor
     * 
     * @param p Current price
     * @param twenty 20-period SMA value
     * @param fifty 50-period SMA value
     */
    SMA(double p, double twenty, double fifty);
};

/**
 * @class MovingAverage
 * @brief Trading strategy based on Simple Moving Averages
 * 
 * Implements a trading strategy that:
 * - Calculates 20-period and 50-period SMAs
 * - Generates buy signals when short SMA crosses above long SMA
 * - Generates sell signals when short SMA crosses below long SMA
 */
class MovingAverage : public Trader {
  public:
    /**
     * @brief Constructs a new MovingAverage instance
     */
    MovingAverage();

    /**
     * @brief Handles new price updates
     * 
     * Updates SMA calculations and makes trading decisions
     * when new prices are received.
     * 
     * @param newPrice The new stock price
     */
    void notify(double newPrice) override;
  
  private:
    /**
     * @brief Updates SMA calculations with new price
     * 
     * @param price The new price to incorporate
     */
    void updateData(double price);

    /**
     * @brief Makes trading decisions based on SMA crossovers
     * 
     * Generates buy/sell signals when the short SMA crosses
     * the long SMA.
     */
    void decideToBuyOrSell();

    std::deque<SMA> sma;  ///< Queue of SMA data points
    double sma_short_total;  ///< Running total for short SMA
    int sma_short_count;     ///< Number of prices in short SMA
    double sma_long_total;   ///< Running total for long SMA
    int sma_long_count;      ///< Number of prices in long SMA
};
