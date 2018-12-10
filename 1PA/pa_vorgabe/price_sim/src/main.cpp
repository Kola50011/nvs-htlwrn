
#include <iostream>
#include <string>
#include <thread>
#include "price_info.h"
#include "producer.h"
#include "result_queue.h"

using namespace std;

void Consumer(string name, PriceInfo &priceInfo)
{
    while (true)
    {
        cout << name + ": " + to_string(priceInfo.get()) + "\n"
             << flush;
    }
}

void NewValueThread(ResultQueue &resultQueue)
{
    while (true)
    {
        cerr << "new value: " + to_string(resultQueue.take()) << endl;
    }
}

int main()
{
    ResultQueue resultQueue{};
    PriceInfo priceInfo{5, resultQueue};
    Producer producer{priceInfo};

    thread newValueDaemon{NewValueThread, ref(resultQueue)};
    newValueDaemon.detach();

    thread c1{Consumer, "Consumer1", ref(priceInfo)};
    thread c2{Consumer, "Consumer2", ref(priceInfo)};
    thread c3{Consumer, "Consumer3", ref(priceInfo)};
    thread producerThreader{producer};

    c1.join();
    c2.join();
    c3.join();
    producerThreader.join();

    return 0;
}
