#include "breakout.h"
#include "../trader.h"

Breakout::Breakout() {}

void Breakout::notify(double newPrice) {
  std::cout << "New price: " << newPrice << "\n";
}