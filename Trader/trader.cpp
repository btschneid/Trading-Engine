#include "trader.h"
#include "../Stock-Market/stock_data.h"
#include "portfolio.h"
#include "../Trading-Engine/engine.h"

Trader::Trader() : balance(1000000), numberStocksOwn(0), count(0) {}

void Trader::queueUpBuy(double price) {
  engine->processBuy(*this, price);
}

void Trader::buy(double price) {
  if (price > balance) {
    return;
  }

  balance -= price;
  numberStocksOwn += 1;
  portfolio.addStock(price, 1);

}

void Trader::queueUpSell(double price) {
  engine->processSell(*this, price);
}

void Trader::sell(double price) {
  if (numberStocksOwn <= 0) {
    return;
  }
  balance += price;
  numberStocksOwn -= 1;
  portfolio.removeStock(price, 1);
}

double Trader::getBalance() {
  return balance;
}

void Trader::setBalance(double bal) {
  balance = bal;
}

void Trader::setEngine(Engine *eng) {
  engine = eng;
}

void Trader::print(std::string type, bool history) {
  for (int i = 0; i < numberStocksOwn; i++) {
    queueUpSell(currentPrice);
  }
  while (numberStocksOwn != 0) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  // Average of 252 trading days per year
  portfolio.print(currentPrice, count / 252.0, type, history);
}