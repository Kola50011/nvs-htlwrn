
#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/wait.h> // waitpid
#include <cstdlib>    // exit
#include <thread>
#include <chrono>
#include <csignal>

using namespace std;

int main(int argc, const char *argv[])
{
    if (argc != 2)
        return 0;

    while (true)
    {
        cout << argv[1] << flush;
        std::chrono::milliseconds sleeptime(500);
        std::this_thread::sleep_for(sleeptime);
    }

    return 0;
}
