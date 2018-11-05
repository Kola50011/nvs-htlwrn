#include "philosopher.h"
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

std::mutex Philosopher::out_mutex;

Philosopher::Philosopher(int _number, std::mutex& _leftFork, std::mutex& _rightFork) :
    leftFork(_leftFork),
    rightFork(_rightFork)
{
    number = _number;
}

Philosopher::~Philosopher()
{
}


void Philosopher::eat() {
    println({std::string("aus"), string("gabe")});
    printf("Philosopher %1i is thinking...\n", number);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    printf("Philosopher %1i attempts to get left fork\n", number);
    leftFork.lock();
    printf("Philosopher %1i got left fork. Now he wants the right one...\n", number);    
    rightFork.lock();

    std::this_thread::sleep_for(std::chrono::seconds(2));
    printf("Philosopher %1i finished eating\n", number);    

    leftFork.unlock();
    printf("Philosopher %1i released left fork\n", number);    
    rightFork.unlock();
    printf("Philosopher %1i released right fork\n", number);    
}

void Philosopher::println(const initializer_list<string> list) {
    out_mutex.lock();

    for(string out : list)
    {
        cout << out;
    }    
    cout << endl;

    out_mutex.unlock();
}