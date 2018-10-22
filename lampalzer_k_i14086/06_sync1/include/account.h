#include <mutex>

class Account
{
private:
  int balance;
  std::mutex lck;

public:
  Account(int startAmount);
  ~Account();
  int get_balance();
  void deposit(int amount);
  bool withdraw(int amount);
};

class Depositer
{
public:
  Depositer(Account& account);
  ~Depositer();
};