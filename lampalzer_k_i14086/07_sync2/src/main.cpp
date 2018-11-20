#include <iostream>
#include "workPacket.h"
#include "workQueue.h"
#include <unistd.h>
#include <thread>
#include <chrono>

using namespace std;

void loadsim(WorkQueue &queue)
{
    int i{0};
    while (true)
    {
        printf("B: Waiting to submit work packet %3i\n", i);

        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

        queue.push(WorkPacket{i});
        // rand between 0 - 1
        double randNum = rand() / double(RAND_MAX);
        usleep(randNum * 1000000);

        chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        printf("B: Submitted work packet %3i (%4.3fs)\n", i, duration / 1000.0);
        i++;
    }
}

void worker(int id, WorkQueue &queue)
{
    while (true)
    {
        printf("W%2i: Want work packet\n", id);
        WorkPacket p{queue.pop()};
        printf("W%2i: Got work packet %3i\n", id, p.getId());

        // rand between 1 - 10
        double randNum = rand() % (10 - 1 + 1) + 1;
        usleep(randNum * 1000000);

        printf("W%2i: Processed work packet %3i\n", id, p.getId());
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 1;
    }
    // nicht in {} möglich, da    error: narrowing conversion from ‘int’ to ‘unsigned int’ inside { }
    unsigned int size = stoi(argv[1]);
    WorkQueue queue{size};
    std::thread boss{loadsim, ref(queue)};
    std::thread worker1{worker, 1, ref(queue)};
    std::thread worker2{worker, 2, ref(queue)};
    std::thread worker3{worker, 3, ref(queue)};

    boss.join();
    worker1.join();
    worker2.join();
    worker3.join();
}
