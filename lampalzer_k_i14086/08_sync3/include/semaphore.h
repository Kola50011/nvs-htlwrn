#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

class Semaphore
{
  private:
    unsigned int size;
    std::mutex mtx;
    std::condition_variable notEmpty;

  public:
    Semaphore(unsigned int _size);
    Semaphore();
    ~Semaphore();
    int avaliblePermits();
    void acquire();
    void release();
};