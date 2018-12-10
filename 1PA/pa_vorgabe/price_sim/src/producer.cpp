#include "price_info.h"
#include "producer.h"
#include <iostream>
#include <future>
#include <random>

using namespace std;

Producer::Producer(PriceInfo &_priceInfo) : priceInfo{_priceInfo}
{
}

Producer::~Producer()
{
}

void Producer::operator()()
{
    random_device rd;
    uniform_real_distribution<double> dist(-2.0, 5.0);
    while (true)
    {
        auto fut = async([&] {return dist(rd);});
        priceInfo.set(priceInfo.get() + fut.get());
        // priceInfo.set(priceInfo.get() + dist(rd));
    }
}