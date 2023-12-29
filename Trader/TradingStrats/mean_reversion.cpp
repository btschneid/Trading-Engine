#include "mean_reversion.h"
#include "../trader.h"

MeanReversion::MeanReversion() {}

void MeanReversion::notify(double newPrice) {
  std::cout << "New price: " << newPrice << "\n";
  queueUpBuy(newPrice);
  queueUpSell(newPrice);
}