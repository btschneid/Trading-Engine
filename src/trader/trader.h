#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include "../market/stock_data.h"
#include "portfolio.h"

class Engine;

class Trader {
  public:
    Trader();

    virtual void notify(double newPrice) = 0;

    void queueUpBuy(double price);
    void queueUpSell(double price);

    void buy(double price);
    void sell(double price);

    double getBalance();
    void setBalance(double bal);

    void setEngine(Engine *eng);

    void print(std::string type, bool history);
    
  private:
    Engine *engine;
    double balance;
    int numberStocksOwn;
    Portfolio portfolio;

  protected:
    double currentPrice;
    int count;


};
