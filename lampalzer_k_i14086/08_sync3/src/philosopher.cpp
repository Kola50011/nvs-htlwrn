#include "philosopher.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <utils.h>

using namespace std;

Philosopher::Philosopher(int _number, std::mutex& _leftFork, std::mutex& _rightFork, Semaphore* _semaphore) :
    leftFork(_leftFork),
    rightFork(_rightFork),
    seamphore(_semaphore)
{
    number = _number;
}

Philosopher::~Philosopher()
{
}


void Philosopher::eat() {
    Utils::println(string{"Philosopher "},to_string(number), string{" is thinking..."});
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    if (seamphore != nullptr) {
        seamphore->acquire();
    }
    
    Utils::println("Philosopher ",to_string(number), " attempts to get left fork");
    leftFork.lock();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    Utils::println("Philosopher ",to_string(number), " got left fork. Now he wants the right one...");
    rightFork.lock();

    std::this_thread::sleep_for(std::chrono::seconds(2));
    Utils::println("Philosopher ",to_string(number), " finished eating");

    leftFork.unlock();
    Utils::println("Philosopher ",to_string(number), " released left fork");
    if (seamphore != nullptr) {
        seamphore->release();
    }

    rightFork.unlock();
    Utils::println("Philosopher ",to_string(number), " released right fork");
}
