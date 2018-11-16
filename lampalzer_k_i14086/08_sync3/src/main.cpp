
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
}

void checkArgs(string msg = "")
{
    if (msg != "help" && msg != "nodeadlock")
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
    mutex g1;
    mutex g2;
    mutex g3;

    Semaphore *semaphore;

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
    }

    Philosopher p1{1, g1, g2, semaphore};
    Philosopher p2{2, g2, g3, semaphore};
    Philosopher p3{3, g3, g1, semaphore};

    std::thread t1{&Philosopher::eat, ref(p1)};
    std::thread t2{&Philosopher::eat, ref(p2)};
    std::thread t3{&Philosopher::eat, ref(p3)};

    t1.join();
    t2.join();
    t3.join();
}