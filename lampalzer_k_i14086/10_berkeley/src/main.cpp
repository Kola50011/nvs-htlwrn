
#include <iostream>
#include <thread>
#include <clock.h>
#include <string>
#include "timeSlave.h"
#include "timeMaster.h"
#include "pipe.h"

using namespace std;

int main() {
    TimeSlave ts1("slave1", 1, 0, 1);
    TimeSlave ts2("slave2", 0, 1, 1);
    TimeMaster tm("master", 0, 0, 1);

    tm.setChannel(1, ts1.getChannel());
    tm.setChannel(2, ts2.getChannel());

    thread t1{&TimeSlave::start, ts1};
    thread t2{&TimeSlave::start, (ts2)};
    thread m1{&TimeMaster::start, (tm)};

    t1.join();
    t2.join();
    m1.join();
}
