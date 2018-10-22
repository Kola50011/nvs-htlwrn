#include "account.h"
#include <iostream>
#include <thread>

using namespace std;

Account::Account(int startAmount)
{
    balance = startAmount;
}

Account::~Account() {}

int Account::get_balance()
{
    return balance;
}

void Account::deposit(int amount)
{
    lck.lock();
    balance += amount;
    printf("Deposited %5i %5i\n", amount, balance);
    lck.unlock();
}

bool Account::withdraw(int amount)
{
    lck.lock();
    if (balance - amount >= 0)
    {
        balance -= amount;
        printf("Withdrawn %5i %5i\n", amount, balance);
        lck.unlock();
        return true;
    }
    lck.unlock();
    return false;
}

Depositer::Depositer(Account& account)
{
    for (int i = 0; i < 5; i++)
    {
        this_thread::sleep_for(100ms * i);
        account.deposit(1);
    }
}

Depositer::~Depositer()
{
}