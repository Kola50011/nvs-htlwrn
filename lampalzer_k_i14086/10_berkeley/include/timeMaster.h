#pragma once

#include <string>
#include "clock.h"
#include "channel.h"

using namespace std;

class TimeMaster
{
  private:
    string name;
    Clock clock;
    Channel* channel1;
    Channel* channel2;
  public:
    TimeMaster(string _name, int hours, int minutes, int seconds) : name{_name}
    {
        clock = Clock(_name, hours, minutes, seconds);
        
    };

    void start()
    {
        clock();
    }

    void setChannel(int num, Channel* channel) {
        if (num == 1) {
            channel1 = channel;
        } else {
            channel2 = channel;
        }
    }

};
