#pragma once

#include <string>
#include "clock.h"
#include "channel.h"

using namespace std;

class TimeMaster
{
  private:
    string name;
    Channel *channel1;
    Channel *channel2;
    Clock clock;

  public:
    TimeMaster(string _name, int hours, int minutes, int seconds) : name{_name}
    {
        clock = Clock(_name, hours, minutes, seconds);
    };

    void syncTime()
    {
        while (true)
        {
            this_thread::sleep_for(5s);
            channel1->getMasterPipe() << 0;
            channel2->getMasterPipe() << 0;

            long timeSlave1;
            channel1->getSlavePipe() >> timeSlave1;
            long timeSlave2;
            channel2->getSlavePipe() >> timeSlave2;
            long ownTime = clock.toTime();

            long finalTime = timeSlave1 + timeSlave2 + ownTime;
            finalTime = finalTime / 3;

            channel1->getMasterPipe() << finalTime;
            channel2->getMasterPipe() << finalTime;
            clock.fromTime(finalTime);
        }
    }

    void start()
    {
        thread clockThread{ref(clock)};
        syncTime();
        clockThread.join();
    }

    void setChannel(int num, Channel *channel)
    {
        if (num == 1)
        {
            channel1 = channel;
        }
        else
        {
            channel2 = channel;
        }
    }

    void setTimeMonoton(bool value)
    {
        clock.setTimeMonoton(value);
    }

    void setClockSpeed(int speed)
    {
        clock.setClockSpeed(speed);
    }
};
