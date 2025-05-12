#include "stock_data.h"

// Default constructor initializes empty values
StockData::StockData() {}

// Parameterized constructor sets all fields
StockData::StockData(std::string _symbol, std::string _date, double _close) 
  : symbol(_symbol), date(_date), close(_close) {}