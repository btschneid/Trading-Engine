#include "moving_avg.h"
#include "../trader.h"

// Default constructor creates empty instance with zero values
SMA::SMA() {}

// Parameterized constructor initializes all fields
SMA::SMA(double p, double twenty, double fifty) {
  price = p;
  sma_short = twenty;
  sma_long = fifty;
}

// Initialize running totals for both short and long SMAs
MovingAverage::MovingAverage() : sma_short_total(0), sma_short_count(0), sma_long_total(0), sma_long_count(0) {}

void MovingAverage::notify(double newPrice) {
  currentPrice = newPrice;
  updateData(newPrice);
  decideToBuyOrSell();
  count += 1;
}

// Implementation maintains separate running totals for 20 and 50 period SMAs
// Uses a sliding window approach to efficiently update both averages
void MovingAverage::updateData(double price) {
  double updateVal = price;

  // Update 20-period SMA
  if (sma_short_count >= 20) {
    sma_short_total += updateVal - sma[sma.size() - 20].price;
  } else {
    sma_short_total += updateVal;
  }

  // Update 50-period SMA
  if (sma_long_count >= 50) {
    sma_long_total += updateVal - sma.front().price;
    sma.pop_front();
  } else {
    sma_long_total += updateVal;
  }

  sma_short_count += 1;
  sma_long_count += 1;
  
  // Add new data point with current SMAs
  sma.push_back({updateVal, 
                sma_short_total / std::min(sma_short_count, 20), 
                sma_long_total / std::min(sma_long_count, 50)});
}

// Implementation checks for SMA crossovers to generate trading signals
// Requires 50 data points to ensure both SMAs are fully initialized
void MovingAverage::decideToBuyOrSell() {
  // Need at least 50 data points for valid signals
  if (sma.size() < 50) {
    return;
  }

  // Check for bullish crossover (20 crosses above 50)
  if ((sma[sma.size() - 2].sma_short < sma[sma.size() - 2].sma_long) && 
      (sma.back().sma_short >= sma.back().sma_long)) {
    queueUpBuy(sma.back().price);
  }
  // Check for bearish crossover (20 crosses below 50)
  else if ((sma[sma.size() - 2].sma_short > sma[sma.size() - 2].sma_long) && 
           (sma.back().sma_short <= sma.back().sma_long)) {
    queueUpSell(sma.back().price);
  }
}