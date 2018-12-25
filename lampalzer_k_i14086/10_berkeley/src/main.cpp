
#include <iostream>
#include <thread>
#include <clock.h>
#include <string>
#include "timeSlave.h"
#include "timeMaster.h"
#include "pipe.h"

using namespace std;

int main() {
    Clock::clockSpeed = 1000;

    TimeSlave ts1("slave1", 0, 0, 1);
    TimeSlave ts2("slave2", 0, 0, 5);
    TimeMaster tm("master", 0, 0, 10);

    ts1.getChannel()->setLatency(1);
    ts2.getChannel()->setLatency(3);

    tm.setChannel(1, ts1.getChannel());
    tm.setChannel(2, ts2.getChannel());

    thread t1{&TimeSlave::start, ref(ts1)};
    thread t2{&TimeSlave::start, ref(ts2)};
    thread m1{&TimeMaster::start, ref(tm)};

    t1.join();
    t2.join();
    m1.join();
}
