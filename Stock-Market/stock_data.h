#ifndef STOCK_DATA_H
#define STOCK_DATA_H

#include <iostream>
#include <string>

struct StockData {
  std::string symbol;
  std::string date;
  double open;
  double high;
  double low;
  double close;
  double adj_close;
  unsigned long long volume;

  StockData();

  StockData(std::string _symbol, std::string _date, double _open, double _high, 
  double _low, double _close, double _adj_close, unsigned long long _volume);
};

#endif // STOCK_DATA_H