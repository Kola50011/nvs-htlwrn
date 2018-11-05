#pragma once

#include <mutex>
#include <vector>
#include <initializer_list>
#include <string>

class Philosopher
{
  private:
    int number;
    std::mutex& leftFork;
    std::mutex& rightFork;
    static void println(const std::initializer_list<std::string> list);
    static std::mutex out_mutex;

  public:
    Philosopher(int _number, std::mutex& _leftFork, std::mutex& _rightFork);
    ~Philosopher();
    void eat();
};