/**
 * @file trader.h
 * @brief Abstract base class for trading strategies
 * 
 * This file defines the Trader class which serves as the base class for all
 * trading strategies. It provides common functionality for managing trades,
 * portfolio, and interaction with the trading engine.
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include "../market/stock_data.h"
#include "portfolio.h"

class Engine;

/**
 * @class Trader
 * @brief Abstract base class for implementing trading strategies
 * 
 * The Trader class provides the interface and common functionality for all
 * trading strategies. It manages the trader's balance, portfolio, and
 * interaction with the trading engine. Derived classes must implement
 * the notify() method to define their specific trading logic.
 */
class Trader {
  public:
    /**
     * @brief Constructs a new Trader instance
     * 
     * Initializes the trader's balance and portfolio.
     */
    Trader();

    /**
     * @brief Pure virtual method to handle price updates
     * 
     * This method must be implemented by derived classes to define
     * their specific trading strategy when prices change.
     * 
     * @param newPrice The new price of the stock
     */
    virtual void notify(double newPrice) = 0;

    /**
     * @brief Queues a buy request with the trading engine
     * 
     * @param price The price at which to execute the buy
     */
    void queueUpBuy(double price);

    /**
     * @brief Queues a sell request with the trading engine
     * 
     * @param price The price at which to execute the sell
     */
    void queueUpSell(double price);

    /**
     * @brief Executes a buy order
     * 
     * @param price The price at which to buy
     */
    void buy(double price);

    /**
     * @brief Executes a sell order
     * 
     * @param price The price at which to sell
     */
    void sell(double price);

    /**
     * @brief Gets the current balance
     * 
     * @return The current balance
     */
    double getBalance();

    /**
     * @brief Sets the trader's balance
     * 
     * @param bal The new balance value
     */
    void setBalance(double bal);

    /**
     * @brief Sets the trading engine instance
     * 
     * @param eng Pointer to the trading engine
     */
    void setEngine(Engine *eng);

    /**
     * @brief Prints trading information
     * 
     * @param type The type of information to print
     * @param history Whether to include trading history
     */
    void print(std::string type, bool history);
    
  private:
    Engine *engine;      ///< Pointer to the trading engine
    double balance;      ///< Current balance
    int numberStocksOwn; ///< Number of stocks currently owned
    Portfolio portfolio; ///< Portfolio of stocks

  protected:
    double currentPrice; ///< Current price of the stock
    int count;          ///< Counter for tracking operations
};
