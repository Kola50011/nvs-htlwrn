#pragma once

#include <string>
#include "clock.h"
#include "channel.h"
#include "pipe.h"
#include <thread>

using namespace std;

class TimeSlave
{
  private:
    string name;
    Channel *channel;
    Clock clock;

  public:
    TimeSlave(string _name, int hours, int minutes, int seconds) : name{_name}
    {
        clock = Clock(_name, hours, minutes, seconds);
        channel = new Channel();
    };

    void syncTime()
    {
        Pipe<long> &masterPipe = channel->getMasterPipe();
        Pipe<long> &slavePipe = channel->getSlavePipe();

        long time;
        while (masterPipe >> time)
        {
            if (time == 0)
            {
                slavePipe << clock.toTime();
            }
            else
            {
                clock.fromTime(time);
            }
        }
    }

    void start()
    {
        thread clockThread{ref(clock)};
        syncTime();
        clockThread.join();
    }

    Channel *getChannel()
    {
        return channel;
    }

    void setTimeMonoton(bool value)
    {
        clock.setTimeMonoton(value);
    }

    void setClockSpeed(int speed) {
        clock.setClockSpeed(speed);
    }
};
