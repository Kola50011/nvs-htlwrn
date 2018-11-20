#include <iostream>
#include <thread>
#include <philosopher.h>
#include <mutex>
#include "semaphore.h"

using namespace std;

void printHelp()
{
    cout << "Usage: dining [OPTION]..." << endl;
    cout << "Options:" << endl;
    cout << "\tnodeadlock enable deadlock prevention" << endl;
    cout << "\thelp display this help and exit" << endl;
    cout << "\tlivelock enables a timeout on the forks" << endl;
}

void checkArgs(string msg = "")
{
    if (msg != "help" && msg != "nodeadlock" && msg != "livelock")
    {
        cout << "Error: unrecognized command line option '" << msg << "'" << endl;
        printHelp();
        exit(1);
    }
    if (msg == "help")
    {
        printHelp();
        exit(1);
    }
}

int main(int argc, const char *argv[])
{
    timed_mutex g1;
    timed_mutex g2;
    timed_mutex g3;
    timed_mutex g4;
    timed_mutex g5;

    Semaphore *semaphore = nullptr;
    int timeout = 9999999;

    if (argc > 2)
    {
        printHelp();
        return 1;
    }
    else if (argc == 2)
    {
        checkArgs(argv[1]);

        if (argv[1] == string("nodeadlock"))
        {
            semaphore = new Semaphore(2);
        }
        else if (argv[1] == string("livelock"))
        {
            timeout = 3;
        }
    }

    Philosopher p1{1, g1, g2, semaphore, timeout};
    Philosopher p2{2, g2, g3, semaphore, timeout};
    Philosopher p3{3, g3, g4, semaphore, timeout};
    Philosopher p4{3, g4, g5, semaphore, timeout};
    Philosopher p5{3, g5, g1, semaphore, timeout};

    std::thread t1{&Philosopher::eat, ref(p1)};
    std::thread t2{&Philosopher::eat, ref(p2)};
    std::thread t3{&Philosopher::eat, ref(p3)};
    std::thread t4{&Philosopher::eat, ref(p4)};
    std::thread t5{&Philosopher::eat, ref(p5)};

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}