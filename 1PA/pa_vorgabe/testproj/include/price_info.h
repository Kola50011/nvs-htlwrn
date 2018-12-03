#pragma once

#include <chrono>
#include <thread>
#include "result_queue.h"

using namespace std;

class PriceInfo
{
  private:
    double price;
    ResultQueue &resultQueue;

  public:
    PriceInfo(double _price, ResultQueue &_resultQueue)
        : price{_price}, resultQueue{_resultQueue} {};

    ~PriceInfo(){};

    double get()
    {
        this_thread::sleep_for(250ms);
        return price;
    };

    void set(double _price)
    {
        std::this_thread::sleep_for(500ms);
        double before{price};
        price = _price > 0 ? _price : 0;

        if (price != before)
        {
            resultQueue.put(price);
        }
    };
};