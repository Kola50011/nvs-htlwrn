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
  std::timed_mutex &leftFork;
  std::timed_mutex &rightFork;
  Semaphore *seamphore;
  int forkTimeout;
  void getForks();
  void releaseForks();

public:
  Philosopher(int _number, std::timed_mutex &_leftFork, std::timed_mutex &_rightFork, Semaphore *_semaphore, int _forkTimeout);
  ~Philosopher();
  void eat();
};