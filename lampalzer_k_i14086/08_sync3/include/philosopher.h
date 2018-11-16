#pragma once

#include <mutex>
#include <vector>
#include <initializer_list>
#include <string>
#include "semaphore.h"

class Philosopher
{
  private:
    int number;
    std::mutex& leftFork;
    std::mutex& rightFork;
    Semaphore* seamphore;

  public:
    Philosopher(int _number, std::mutex& _leftFork, std::mutex& _rightFork, Semaphore* _semaphore);
    ~Philosopher();
    void eat();
};