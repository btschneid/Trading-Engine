#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <iostream>
#include "../trader.h"

class Breakout : public Trader {
  public:
    Breakout();

    void notify(double newPrice) override;
  
  private:

};

#endif // BREAKOUT_H
