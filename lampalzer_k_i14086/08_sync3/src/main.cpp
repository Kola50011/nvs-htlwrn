
#include <iostream>
#include <thread>
#include <philosopher.h>
#include <mutex>

using namespace std;

int main() {
    mutex g1;
    mutex g2;
    mutex g3;

    Philosopher p1{1, g1, g2};
    Philosopher p2{2, g2, g3};
    Philosopher p3{3, g3, g1};

    std::thread t1{&Philosopher::eat, ref(p1)};
    std::thread t2{&Philosopher::eat, ref(p2)};
    std::thread t3{&Philosopher::eat, ref(p3)};

    t1.join();
    t2.join();
    t3.join();
}
