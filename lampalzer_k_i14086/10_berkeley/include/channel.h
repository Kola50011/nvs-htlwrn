#pragma once

#include "pipe.h"

class Channel
{
  private:
    Pipe<long> masterPipe;
    Pipe<long> slavePipe;

  public:
    Channel(){};
    ~Channel(){};

    Pipe<long> &getMasterPipe()
    {
        return masterPipe;
    }

    Pipe<long> &getSlavePipe()
    {
        return slavePipe;
    }

    Channel operator=(const Channel &);

    void setLatency(int latency) {
        masterPipe.setLatency(latency);
        slavePipe.setLatency(latency);
    }
};