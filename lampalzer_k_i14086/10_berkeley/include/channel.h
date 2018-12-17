#pragma once

#include "pipe.h"

class Channel
{
  private:
    Pipe<long> pipe1;
    Pipe<long> pipe2;

  public:
    Channel();
    ~Channel();

    Pipe<long> &getPipe(int num)
    {
        if (num == 1)
        {
            return pipe1;
        }
        return pipe2;
    }

    Channel operator=(const Channel &);
};