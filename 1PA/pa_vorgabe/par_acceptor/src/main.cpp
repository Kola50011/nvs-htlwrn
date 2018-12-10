#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include "calc.h"
#include <thread>
#include "semaphore.h"

using namespace std;

pid_t fork(int num)
{
    auto pid{fork()};
    if (pid == 0)
    {
        if (num % 2 == 0)
        {
            quick_exit(EXIT_SUCCESS);
        }
        else
        {
            quick_exit(EXIT_FAILURE);
        }
    }
    else
    {
        return pid;
    }
}

void printName(string name, Semaphore& semaphore) {
    semaphore.acquire();
    cout << name << endl;
    semaphore.release();
}

void calc()
{
    Calc calc;
    thread addThread{[&] {
        calc.add(1);
        calc.add(2);
        calc.add(3);
    }};

    thread mulThread{[&] {
        calc.mul(1);
        calc.mul(2);
        calc.mul(3);
    }};

    addThread.join();
    mulThread.join();

    cout << calc.value() << endl;
}

int main(int argc, char *argv[])
{
    calc();

    Semaphore semaphore{1};
    thread t1{printName, "Thread A", ref(semaphore)};
    thread t2{printName, "Thread B", ref(semaphore)};
    t1.join();
    t2.join();

    if (argc != 3)
    {
        return 1;
    }

    int num1{};
    int num2{};

    try
    {
        num1 = stoi(argv[1]);
        num2 = stoi(argv[2]);
    }
    catch (...)
    {
        return 2;
    }

    pid_t pid1 = fork(num1);
    pid_t pid2 = fork(num2);

    int status1;
    int status2;
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    if (status1 == EXIT_SUCCESS && status2 == EXIT_SUCCESS)
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }
    return 0;
}
