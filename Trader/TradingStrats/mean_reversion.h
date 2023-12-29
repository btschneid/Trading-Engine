#ifndef MEAN_REVERSION_H
#define MEAN_REVERSION_H

#include <iostream>
#include "../trader.h"

class MeanReversion : public Trader {
  public:
    MeanReversion();

    void notify(double newPrice) override;
  
  private:

};

#endif // MEAN_REVERSION_H
