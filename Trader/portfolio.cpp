#include "portfolio.h"
#include "../Stock-Market/stock_data.h"

StockInfo::StockInfo() : symbol(""), quantity(0), 
current_stock_price(0), market_value(0), cost_basis(0), 
gain_or_loss(0) {}

void StockInfo::updateBuy(double price, int q) {
  quantity += q;
  current_stock_price = price;
  market_value = current_stock_price * quantity;
  cost_basis += price * q;
  gain_or_loss = market_value - cost_basis;
}

void StockInfo::updateSell(double price, int q) {
  int num = q;
  quantity -= q;
  current_stock_price = price;
  market_value = current_stock_price * quantity;

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

void StockInfo::updateVals(double closingPrice) {
  current_stock_price = closingPrice;
  market_value = current_stock_price * quantity;
  gain_or_loss = market_value - cost_basis;
}

Portfolio::Portfolio() {
}

void Portfolio::addStock(double price, int quantity) {
  info.updateBuy(price, quantity);
  info.shares.push(std::make_pair(price, quantity));
  stockHistory.push_back(std::make_pair("Buy", price));
}

void Portfolio::removeStock(double price, int quantity) {
  info.updateSell(price, quantity);
  stockHistory.push_back(std::make_pair("Sell", price));
}

void Portfolio::print(double closing) {
  double b = 0;
  double s = 0;
  std::cout << "-------------------------------------------------\n";
  info.updateVals(closing);

  std::cout << "History:\n";
  for (const auto& pair : stockHistory) {
    const std::string& action = pair.first;
    const double& stockInfo = pair.second;
    std::cout << action << ": " << stockInfo << "\n";
    if (action == "Buy") {
      b += stockInfo;
    } else {
      s += stockInfo;
    }
  }

  std::cout << "Gain/Loss: " << (s - b) << "$ or " << ((s - b) / b) * 100 << "%\n";

  std::cout << "-------------------------------------------------\n";
}

int Portfolio::getNumberOfStock() {
  return info.quantity;
}