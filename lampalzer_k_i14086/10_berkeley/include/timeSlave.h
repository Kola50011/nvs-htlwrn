#pragma once

#include <string>
#include "clock.h"
#include "channel.h"

using namespace std;

class TimeSlave
{
  private:
    string name;
    Clock clock;
    Channel* channel;

  public:
    TimeSlave(string _name, int hours, int minutes, int seconds) : name{_name}
    {
        clock = Clock(_name, hours, minutes, seconds);
    };

    void start() {
        clock();
    }

    Channel* getChannel() {
        return channel;
    }
};
