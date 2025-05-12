#ifndef STOCK_DATA_H
#define STOCK_DATA_H

#include <iostream>
#include <string>

struct StockData {
  std::string symbol;
  std::string date;
  double close;

  StockData();

  StockData(std::string _symbol, std::string _date, double _close);
};

#endif // STOCK_DATA_H