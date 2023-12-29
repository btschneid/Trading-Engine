#include "stock_data.h"

StockData::StockData() {}

StockData::StockData(std::string _symbol, std::string _date, double _open, double _high, 
  double _low, double _close, double _adj_close, unsigned long long _volume) 
  : symbol(_symbol), date(_date), open(_open), high(_high), low(_low), close(_close), 
  adj_close(_adj_close), volume(_volume) {}