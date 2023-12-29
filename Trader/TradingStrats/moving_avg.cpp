#include "moving_avg.h"
#include "../trader.h"

SMA::SMA() {}

SMA::SMA(double p, double twenty, double fifty) {
  price = p;
  sma20 = twenty;
  sma50 = fifty;
}

MovingAverage::MovingAverage() : sma20_total(0), sma20_count(0), sma50_total(0), sma50_count(0) {
}

void MovingAverage::notify(double newPrice) {
  currentPrice = newPrice;
  updateData(newPrice);
  decideToBuyOrSell();
  count += 1;
}

void MovingAverage::updateData(double price) {
  double updateVal = price;

  if (sma20_count >= 20) {
    sma20_total += updateVal - sma[sma.size() - 20].price;
  } else {
    sma20_total += updateVal;
  }

  if (sma50_count >= 50) {
    sma50_total += updateVal - sma.front().price;
    sma.pop_front();
  } else {
    sma50_total += updateVal;
  }

  sma20_count += 1;
  sma50_count += 1;
  
  sma.push_back({updateVal, sma20_total / std::min(sma20_count, 20), sma50_total / std::min(sma50_count, 50)});
}

void MovingAverage::decideToBuyOrSell() {
  if (sma.size() < 50) {
    return;
  }

  // 20 crosses 50 from below buy
  // 20 crosses 50 from above sell

  if ((sma[sma.size() - 2].sma20 < sma[sma.size() - 2].sma50) && 
  (sma.back().sma20 >= sma.back().sma50)) {
    queueUpBuy(sma.back().price);
  } else if ((sma[sma.size() - 2].sma20 > sma[sma.size() - 2].sma50) && 
  (sma.back().sma20 <= sma.back().sma50)) {
    queueUpSell(sma.back().price);
  }
}