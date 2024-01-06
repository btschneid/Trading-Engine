#include "moving_avg.h"
#include "../trader.h"

SMA::SMA() {}

SMA::SMA(double p, double twenty, double fifty) {
  price = p;
  sma_short = twenty;
  sma_long = fifty;
}

MovingAverage::MovingAverage() : sma_short_total(0), sma_short_count(0), sma_long_total(0), sma_long_count(0) {}

void MovingAverage::notify(double newPrice) {
  currentPrice = newPrice;
  updateData(newPrice);
  decideToBuyOrSell();
  count += 1;
}

void MovingAverage::updateData(double price) {
  double updateVal = price;

  // Get moving average of size 20
  if (sma_short_count >= 20) {
    sma_short_total += updateVal - sma[sma.size() - 20].price;
  } else {
    sma_short_total += updateVal;
  }

  // Get moving average of size 50
  if (sma_long_count >= 50) {
    sma_long_total += updateVal - sma.front().price;
    sma.pop_front();
  } else {
    sma_long_total += updateVal;
  }

  sma_short_count += 1;
  sma_long_count += 1;
  
  sma.push_back({updateVal, sma_short_total / std::min(sma_short_count, 20), sma_long_total / std::min(sma_long_count, 50)});
}

void MovingAverage::decideToBuyOrSell() {
  if (sma.size() < 50) {
    return;
  }

  // 20 crosses 50 from below buy
  // 20 crosses 50 from above sell

  if ((sma[sma.size() - 2].sma_short < sma[sma.size() - 2].sma_long) && 
  (sma.back().sma_short >= sma.back().sma_long)) {
    queueUpBuy(sma.back().price);
  } else if ((sma[sma.size() - 2].sma_short > sma[sma.size() - 2].sma_long) && 
  (sma.back().sma_short <= sma.back().sma_long)) {
    queueUpSell(sma.back().price);
  }
}