
#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/wait.h> // waitpid
#include <cstdlib>    // exit
#include <thread>
#include <chrono>
#include <csignal>

using namespace std;

int main()
{
    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        execl("./charout", "./charout", getenv("ABA_LETTER_A") ? getenv("ABA_LETTER_A") : "A", 0);
    }
    else
    {
        pid_t pid2 = fork();
        if (pid2 == 0)
        {
            execl("./charout", "./charout", getenv("ABA_LETTER_B") ? getenv("ABA_LETTER_B") : "B", 0);
        }

        for (int i = 0; i < 6; i++)
        {
            cout << "B" << flush;
            std::chrono::milliseconds sleeptime(500);
            std::this_thread::sleep_for(sleeptime);
        }
        kill(pid1, SIGKILL);
        kill(pid2, SIGKILL);
        exit(EXIT_SUCCESS);
    }
    return 0;
}
