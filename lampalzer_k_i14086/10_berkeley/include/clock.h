#pragma once

#include "timeutils.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <mutex>

using namespace std;

class Clock
{
  private:
    chrono::time_point<chrono::system_clock> curr_time;
    string name;
    static mutex mtx;
    
  public:
    static int clockSpeed;
    
    Clock(){};
    Clock(string _name) : name{_name}
    {
    };

    Clock(string _name, int hours, int minutes, int seconds)
    {
        curr_time = chrono::system_clock::now();
        curr_time = TIME_UTILS_H::set_time(curr_time, hours, minutes, seconds);
        name = _name;
    }

    void operator()()
    {
        while (true)
        {
            {
                lock_guard<mutex> lg(mtx);
                cout << name << ": " << curr_time << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(clockSpeed));
            curr_time += 1s;
        }
    }

    void set_time(int hours, int minutes, int seconds)
    {
        curr_time = TIME_UTILS_H::set_time(curr_time, hours, minutes, seconds);
    }

    tuple<int, int, int> get_time()
    {
        return TIME_UTILS_H::get_time(curr_time);
    }

    long toTime()
    {
        return chrono::system_clock::to_time_t(curr_time);
    }

    void fromTime(long time)
    {
        curr_time = chrono::system_clock::from_time_t(time);
    }
};

mutex Clock::mtx;
int Clock::clockSpeed{1000};