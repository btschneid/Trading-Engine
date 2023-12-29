#include "mean_reversion.h"
#include "../trader.h"

MovingMean::MovingMean() {}

MovingMean::MovingMean(double p, double _sma, double _diff, int _sig) :
price(p), sma(_sma), diff(_diff), signal(_sig) {}

MeanReversion::MeanReversion() : sma_total(0), sma_count(0), window(50) {}

void MeanReversion::notify(double newPrice) {
  currentPrice = newPrice;
  updateData(newPrice);
  decideToBuyOrSell();
  count += 1;
}

void MeanReversion::updateData(double price) {
  double updateVal = price;

  if (sma_count >= window) {
    sma_total += updateVal - moving_mean.front().price;
    moving_mean.pop_front();
  } else {
    sma_total += updateVal;
  }

  sma_count += 1;

  double sma_val = sma_total / std::min(sma_count, window);
  double diff = updateVal - sma_val;

  int signal = 1;
  if (diff > 0) {
    signal = -1;
  }
  
  moving_mean.push_back({updateVal, sma_val, diff, signal});
}

void MeanReversion::decideToBuyOrSell() {
  if (moving_mean.size() < 50) {
    return;
  }

  // Signal = -1: Buy, Signal = 1: Sell

  if (moving_mean[moving_mean.size() - 2].signal != moving_mean.back().signal) {
    if (moving_mean.back().signal == 1) {

      queueUpBuy(moving_mean.back().price);
    } else {
      queueUpSell(moving_mean.back().price);
    }
  }
}