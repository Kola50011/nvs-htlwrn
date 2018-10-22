
#include <iostream>
#include <thread>
#include "account.h"

using namespace std;

int main() {
    // Punkt 1
    // Account account{0};
    // account.deposit(5);
    // account.withdraw(5);

    Account account{0};

    std::thread t1([&](){
        Depositer{ref(account)};
    });
    
    std::thread t2([&](){
        Depositer{ref(account)};
    });

    t1.join();
    t2.join();
}
