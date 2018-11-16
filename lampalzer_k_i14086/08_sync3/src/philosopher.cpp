#include "philosopher.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <utils.h>

using namespace std;

Philosopher::Philosopher(int _number,
                         std::timed_mutex &_leftFork, std::timed_mutex &_rightFork,
                         Semaphore *_semaphore, int _forkTimeout) : leftFork(_leftFork),
                                                                    rightFork(_rightFork),
                                                                    seamphore(_semaphore),
                                                                    forkTimeout(_forkTimeout)
{
    number = _number;
}

Philosopher::~Philosopher()
{
}

void Philosopher::getForks()
{
    if (seamphore != nullptr)
    {
        seamphore->acquire();
    }

    Utils::println("Philosopher ", to_string(number), " attempts to get left fork");
    leftFork.lock();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    Utils::println("Philosopher ", to_string(number), " got left fork. Now he wants the right one...");
    auto start = std::chrono::steady_clock::now();
    if (!rightFork.try_lock_until(start + std::chrono::seconds(forkTimeout)))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        leftFork.unlock();
        Utils::println("Philosopher ", to_string(number), " released left fork due to timeout getting the right one!");
        std::this_thread::sleep_for(std::chrono::seconds(3));
        getForks();
    }
}

void Philosopher::releaseForks()
{
    leftFork.unlock();
    Utils::println("Philosopher ", to_string(number), " released left fork");
    if (seamphore != nullptr)
    {
        seamphore->release();
    }

    rightFork.unlock();
    Utils::println("Philosopher ", to_string(number), " released right fork");
}

void Philosopher::eat()
{
    Utils::println(string{"Philosopher "}, to_string(number), string{" is thinking..."});
    std::this_thread::sleep_for(std::chrono::seconds(1));

    getForks();

    std::this_thread::sleep_for(std::chrono::seconds(2));
    Utils::println("Philosopher ", to_string(number), " finished eating");

    releaseForks();
}
