#include "portfolio.h"
#include "../market/stock_data.h"

/**
 * @brief Constructs a new StockInfo instance with default values
 * 
 * Initializes all numeric values to 0 and symbol to empty string.
 */
StockInfo::StockInfo() : symbol(""), quantity(0), 
current_stock_price(0), market_value(0), cost_basis(0), 
gain_or_loss(0) {}

/**
 * @brief Updates position information after a buy
 * 
 * Updates quantity, current price, market value, cost basis,
 * and gain/loss based on the new purchase.
 * 
 * @param price Price per share
 * @param q Quantity of shares
 */
void StockInfo::updateBuy(double price, int q) {
  quantity += q;
  current_stock_price = price;
  market_value = current_stock_price * quantity;
  cost_basis += price * q;
  gain_or_loss = market_value - cost_basis;
}

/**
 * @brief Updates position information after a sell
 * 
 * Updates quantity, current price, market value, cost basis,
 * and gain/loss based on the sale. Uses FIFO method for
 * cost basis calculation.
 * 
 * @param price Price per share
 * @param q Quantity of shares
 */
void StockInfo::updateSell(double price, int q) {
  int num = q;
  quantity -= q;
  current_stock_price = price;
  market_value = current_stock_price * quantity;

  // Process shares in FIFO order
  while (shares.size() > 0 && num > 0) {
    int numberOfSharesFront = shares.front().second;
    cost_basis -= shares.front().first * std::min(num, numberOfSharesFront);
    
    if (num >= numberOfSharesFront) {
      shares.pop();
      num -= numberOfSharesFront;
    } else {
      shares.front().second -= num;
      num = 0;
    }
  }

  gain_or_loss = market_value - cost_basis;
}

/**
 * @brief Updates market value and gain/loss based on current price
 * 
 * @param closingPrice Current market price
 */
void StockInfo::updateVals(double closingPrice) {
  current_stock_price = closingPrice;
  market_value = current_stock_price * quantity;
  gain_or_loss = market_value - cost_basis;
}

/**
 * @brief Constructs a new Portfolio instance
 */
Portfolio::Portfolio() {}

/**
 * @brief Adds a stock position to the portfolio
 * 
 * Updates position information and adds the transaction to history.
 * 
 * @param price Price per share
 * @param quantity Number of shares to add
 */
void Portfolio::addStock(double price, int quantity) {
  info.updateBuy(price, quantity);
  info.shares.push(std::make_pair(price, quantity));
  stockHistory.push_back(std::make_pair("Buy", price));
}

/**
 * @brief Removes a stock position from the portfolio
 * 
 * Updates position information and adds the transaction to history.
 * 
 * @param price Price per share
 * @param quantity Number of shares to remove
 */
void Portfolio::removeStock(double price, int quantity) {
  info.updateSell(price, quantity);
  stockHistory.push_back(std::make_pair("Sell", price));
}

/**
 * @brief Prints portfolio performance information
 * 
 * Displays:
 * - Trading history (if requested)
 * - Total buy and sell amounts
 * - Yearly gain/loss percentage (if years > 0)
 * 
 * @param closing Current closing price
 * @param y Years of trading history
 * @param type Type of information to print
 * @param history Whether to include trading history
 */
void Portfolio::print(double closing, double y, std::string type, bool history) {
  double b = 0;  // Total buy amount
  double s = 0;  // Total sell amount
  
  std::cout << "-------------------------------------------------\n";
  info.updateVals(closing);

  std::cout << type << "'s History:\n";
  for (const auto& pair : stockHistory) {
    const std::string& action = pair.first;
    const double& stockInfo = pair.second;
    if (history) {
      std::cout << action << ": " << stockInfo << "\n";
    }
    if (action == "Buy") {
      b += stockInfo;
    } else {
      s += stockInfo;
    }
  }
  
  // Calculate and display yearly return if applicable
  if (y > 0) {
    std::cout << "Yearly Gain/Loss: " << (s / b) / y * 100 << "%\n";
  }

  std::cout << "-------------------------------------------------\n";
}

/**
 * @brief Gets the total number of stocks in the portfolio
 * 
 * @return Number of stocks
 */
int Portfolio::getNumberOfStock() {
  return info.quantity;
}