#include "timeutils.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <string>

using namespace std;

class Clock
{
  private:
    chrono::time_point<chrono::system_clock> curr_time;
    string name;

  public:
    Clock(string _name) : name{_name}
    {
        curr_time = std::chrono::system_clock::now();
    };

    Clock(string _name, int hours, int minutes, int seconds)
    {
        curr_time = std::chrono::system_clock::now();
        set_time(curr_time, hours, minutes, seconds);
        name = _name;
    }

    void operator()()
    {
        while (true)
        {
            cout << name << ": " << curr_time << endl;
            this_thread::sleep_for(1s);
            curr_time += 1s;
        }
    }
};
