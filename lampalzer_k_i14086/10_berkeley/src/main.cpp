
#include <iostream>
#include <thread>
#include <clock.h>
#include <string>
#include "timeSlave.h"
#include "timeMaster.h"
#include "pipe.h"

using namespace std;

void createTimeSlave(string name) {
    TimeSlave ts(name, 0, 0, 0);
    ts.start();
}

void createTimeMaster(string name) {
    TimeMaster tm(name, 0, 0, 0);
    tm.start();
}

int main() {
    thread s1{createTimeSlave, "slave1"};
    thread s2{createTimeSlave, "slave2"};
    thread m1{createTimeMaster, "master"};

    s1.join();
    s2.join();
    m1.join();
}
