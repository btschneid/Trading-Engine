#include "trader.h"
#include "../market/stock_data.h"
#include "portfolio.h"
#include "../core/engine.h"

// Initialize trader with $1M starting balance and no positions
Trader::Trader() : balance(1000000), numberStocksOwn(0), count(0) {}

/**
 * @brief Queues a buy request with the trading engine
 * 
 * @param price The price at which to execute the buy
 */
void Trader::queueUpBuy(double price) {
  engine->processBuy(*this, price);
}

/**
 * @brief Executes a buy order if sufficient funds are available
 * 
 * Updates balance, stock count, and portfolio when a buy is executed.
 * 
 * @param price The price at which to buy
 */
void Trader::buy(double price) {
  if (price > balance) {
    return;
  }

  balance -= price;
  numberStocksOwn += 1;
  portfolio.addStock(price, 1);
}

/**
 * @brief Queues a sell request with the trading engine
 * 
 * @param price The price at which to execute the sell
 */
void Trader::queueUpSell(double price) {
  engine->processSell(*this, price);
}

/**
 * @brief Executes a sell order if stocks are available
 * 
 * Updates balance, stock count, and portfolio when a sell is executed.
 * 
 * @param price The price at which to sell
 */
void Trader::sell(double price) {
  if (numberStocksOwn <= 0) {
    return;
  }
  
  balance += price;
  numberStocksOwn -= 1;
  portfolio.removeStock(price, 1);
}

/**
 * @brief Gets the current balance
 * 
 * @return The current balance
 */
double Trader::getBalance() {
  return balance;
}

/**
 * @brief Sets the trader's balance
 * 
 * @param bal The new balance value
 */
void Trader::setBalance(double bal) {
  balance = bal;
}

/**
 * @brief Sets the trading engine instance
 * 
 * @param eng Pointer to the trading engine
 */
void Trader::setEngine(Engine *eng) {
  engine = eng;
}

/**
 * @brief Prints trading information and closes all positions
 * 
 * This method:
 * 1. Sells all remaining stocks at current price
 * 2. Waits for all sell orders to complete
 * 3. Prints portfolio performance information
 * 
 * @param type The type of information to print
 * @param history Whether to include trading history
 */
void Trader::print(std::string type, bool history) {
  // Close all positions
  for (int i = 0; i < numberStocksOwn; i++) {
    queueUpSell(currentPrice);
  }
  
  // Wait for all sell orders to complete
  while (numberStocksOwn != 0) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  // Print portfolio performance (assuming 252 trading days per year)
  portfolio.print(currentPrice, count / 252.0, type, history);
}