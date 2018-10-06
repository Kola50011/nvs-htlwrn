#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

void printUsage()
{
    cout << "usage: primes <command> <number>" << endl;
    cout << endl;
    cout << "Commands:" << endl;
    cout << "\ttest ... test if the given number is prime" << endl;
    cout << "\tsieve ... lists all prime numbers up to the given number" << endl;
}

void printCommand()
{
    cout << "Please provide a correct command!" << endl;
    printUsage();
}

void printNumber()
{
    cout << "Please provide a natural number (2 <= number <= 2.000.000.000)" << endl;
    printUsage();
}

void sieve_and_print(int n)
{
    vector<bool> numbers(n, true);
    double root = sqrt(n);
    int i = 2;
    while (i < root)
    {
        if (numbers[i] == true)
        {
            for (int x = 2; i * x <= n; x++)
            {
                numbers[i * x] = false;
            }
        }
        i++;
    }

    for (int i = 2; i <= numbers.size(); i++)
    {
        if (numbers[i] == true)
        {
            cout << i << endl;
        }
    }
}

bool isPrime(unsigned long long int n)
{
    if (n == 2)
    {
        return true;
    }

    if (n % 2 == 0)
    {
        return false;
    }

    float root = sqrt(n);
    for (int i = 3; i <= root; i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

bool isNumber(const string &s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

int main(int argc, char const *argv[])
{
    if (argc == 2 && (string(argv[1]) == "test" || string(argv[1]) == "sieve"))
    {
        printNumber();
        return 0;
    }

    if (argc != 3)
    {
        printCommand();
        return 0;
    }

    if (string(argv[1]) != "test" && string(argv[1]) != "sieve")
    {
        printCommand();
        return 0;
    }

    if (isNumber(argv[2]))
    {
        unsigned long long int inputNumber;
        inputNumber = stoull(argv[2]);
        if (inputNumber < 2)
        {
            printNumber();
            return 0;
        }

        if (string(argv[1]) == "test")
        {
            if (isPrime(inputNumber))
            {
                cout << inputNumber << " is a prime number" << endl;
            }
            else
            {
                cout << inputNumber << " is NOT a prime number" << endl;
            }
            return 0;
        }

        if (string(argv[1]) == "sieve")
        {
            sieve_and_print(inputNumber);
        }
    }
    return 0;
}
