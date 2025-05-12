/**
 * @file mean_reversion.h
 * @brief Mean reversion trading strategy implementation
 * 
 * This file defines the MeanReversion class which implements a trading
 * strategy based on mean reversion principles. It uses a moving average
 * and price deviations to generate buy/sell signals.
 */

#pragma once

#include <iostream>
#include "../trader.h"

/**
 * @struct MovingMean
 * @brief Structure holding mean reversion data
 * 
 * Contains price, moving average, deviation from mean,
 * and trading signal at a given point in time.
 */
struct MovingMean {
    double price;  ///< Current price
    double sma;    ///< Simple Moving Average value
    double diff;   ///< Deviation from the mean
    int signal;    ///< Trading signal (-1: sell, 0: hold, 1: buy)

    /**
     * @brief Default constructor
     */
    MovingMean();

    /**
     * @brief Parameterized constructor
     * 
     * @param p Current price
     * @param _sma Moving average value
     * @param _diff Deviation from mean
     * @param _sig Trading signal
     */
    MovingMean(double p, double _sma, double _diff, int _sig);
};

/**
 * @class MeanReversion
 * @brief Trading strategy based on mean reversion
 * 
 * Implements a trading strategy that:
 * - Calculates a moving average of prices
 * - Measures deviations from the mean
 * - Generates buy signals when price is significantly below mean
 * - Generates sell signals when price is significantly above mean
 */
class MeanReversion : public Trader {
  public:
    /**
     * @brief Constructs a new MeanReversion instance
     */
    MeanReversion();

    /**
     * @brief Handles new price updates
     * 
     * Updates mean calculations and makes trading decisions
     * when new prices are received.
     * 
     * @param newPrice The new stock price
     */
    void notify(double newPrice) override;
  
  private:
    /**
     * @brief Updates mean calculations with new price
     * 
     * @param price The new price to incorporate
     */
    void updateData(double price);

    /**
     * @brief Makes trading decisions based on price deviations
     * 
     * Generates buy/sell signals when price deviates significantly
     * from the moving average.
     */
    void decideToBuyOrSell();

    std::deque<MovingMean> moving_mean;  ///< Queue of mean reversion data points
    double sma_total;  ///< Running total for moving average
    int sma_count;     ///< Number of prices in moving average
    int window;        ///< Size of the moving average window
};
