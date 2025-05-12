#pragma once

#include <iostream>
#include "../trader.h"

struct MovingMean {
  double price;
  double sma;
  double diff;
  int signal;

  MovingMean();

  MovingMean(double p, double _sma, double _diff, int _sig);
};

class MeanReversion : public Trader {
  public:
    MeanReversion();

    void notify(double newPrice) override;
  
  private:
    void updateData(double price);
    void decideToBuyOrSell();

    std::deque<MovingMean> moving_mean;
    double sma_total;
    int sma_count;
    int window;
};
