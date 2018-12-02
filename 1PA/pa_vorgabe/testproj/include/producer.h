#pragma once

#include "price_info.h"

class Producer
{
private:
  PriceInfo &priceInfo;

public:
  explicit Producer(PriceInfo &_priceInfo);
  ~Producer();
  void operator()();
};