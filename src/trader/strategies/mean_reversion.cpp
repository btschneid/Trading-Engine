#include "mean_reversion.h"
#include "../trader.h"

// Default constructor creates empty instance with zero values
MovingMean::MovingMean() {}

// Parameterized constructor initializes all fields
MovingMean::MovingMean(double p, double _sma, double _diff, int _sig) :
price(p), sma(_sma), diff(_diff), signal(_sig) {}

// Initialize running totals and set 50-period window
MeanReversion::MeanReversion() : sma_total(0), sma_count(0), window(50) {}

void MeanReversion::notify(double newPrice) {
  currentPrice = newPrice;
  updateData(newPrice);
  decideToBuyOrSell();
  count += 1;
}

// Implementation uses a sliding window approach to maintain the moving average
// and calculates deviation from mean to generate trading signals
void MeanReversion::updateData(double price) {
  double updateVal = price;

  // Update moving average using sliding window
  if (sma_count >= window) {
    sma_total += updateVal - moving_mean.front().price;
    moving_mean.pop_front();
  } else {
    sma_total += updateVal;
  }

  sma_count += 1;

  // Calculate current moving average and deviation
  double sma_val = sma_total / std::min(sma_count, window);
  double diff = updateVal - sma_val;

  // Determine trading signal based on deviation
  // -1: Price above mean (potential sell)
  //  1: Price below mean (potential buy)
  int signal = 1;
  if (diff > 0) {
    signal = -1;
  }
  
  // Add new data point
  moving_mean.push_back({updateVal, sma_val, diff, signal});
}

// Implementation checks for signal changes to generate buy/sell decisions
// Requires 50 data points for valid signals to ensure statistical significance
void MeanReversion::decideToBuyOrSell() {
  // Need at least 50 data points for valid signals
  if (moving_mean.size() < 50) {
    return;
  }

  // Check for signal changes
  if (moving_mean[moving_mean.size() - 2].signal != moving_mean.back().signal) {
    if (moving_mean.back().signal == 1) {
      // Price moved below mean - buy signal
      queueUpBuy(moving_mean.back().price);
    } else {
      // Price moved above mean - sell signal
      queueUpSell(moving_mean.back().price);
    }
  }
}