#pragma once

#include <iostream>
#include <deque>
#include <limits>

#include "../trader.h"

struct SMA {
  double price;
  double sma_short;
  double sma_long;

  SMA();

  SMA(double p, double twenty, double fifty);
};

class MovingAverage : public Trader {
  public:
    MovingAverage();

    void notify(double newPrice) override;
  
  private:
    void updateData(double price);
    void decideToBuyOrSell();

    std::deque<SMA> sma;
    double sma_short_total;
    int sma_short_count;
    double sma_long_total;
    int sma_long_count;
};
