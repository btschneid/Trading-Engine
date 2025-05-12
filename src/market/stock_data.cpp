#include "stock_data.h"

StockData::StockData() {}

StockData::StockData(std::string _symbol, std::string _date, double _close) 
  : symbol(_symbol), date(_date), close(_close) {}