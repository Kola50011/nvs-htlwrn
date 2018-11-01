#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

#include "workPacket.h"

class WorkQueue
{
  private:
    unsigned int size;
    std::queue<WorkPacket> queue;
    std::mutex mx;
    std::condition_variable notEmptyCv;
    std::condition_variable notFullCv;

  public:
    WorkQueue(unsigned int _size);
    ~WorkQueue();
    void push(WorkPacket workPacket);
    WorkPacket pop();
};