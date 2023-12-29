#ifndef MOVING_AVG_H
#define MOVING_AVG_H

#include <iostream>
#include <deque>
#include <limits>

#include "../trader.h"

struct SMA {
  double price;
  double sma20;
  double sma50;

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
    double sma20_total;
    int sma20_count;
    double sma50_total;
    int sma50_count;
};

#endif // MOVING_AVG_H
