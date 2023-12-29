#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>

#include "../Stock-Market/stock_data.h"

struct StockInfo {
  std::string symbol;
  int quantity;
  double current_stock_price;
  double market_value;
  double cost_basis;
  double gain_or_loss;
  std::queue<std::pair<double, int>> shares;
  StockInfo();

  void updateBuy(double price, int q);
  void updateSell(double price, int q);
  void updateVals(double closingPrice);
};

class Portfolio {
  public:
    Portfolio();

    void addStock(double price, int quantity);
    void removeStock(double price, int quantity);

    int getNumberOfStock();

    void print(double closing);

  private:
    StockInfo info;
    std::vector<std::pair<std::string, double>> stockHistory;

};

#endif // PORTFOLIO_H