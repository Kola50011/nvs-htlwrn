#include <iostream>
#include <math.h>

using namespace std;

void printCommand() {
    cout << "Please provide a command!" << endl;
    printUsage();
}

void printNumber() {
    cout << "Please provide a natural number (2 <= number <= 2.000.000.000)" << endl;
    printUsage();
}

void printUsage() {
    cout << "usage: primes <command> <number>" << endl;
    cout << endl;
    cout << "Commands:" << endl;
    cout << "\ttest ... test if the given number is prime" << endl;
    cout << "\tsieve ... lists all prime numbers up to the given number" << endl;
}

void testPrime(char input) {

}

bool isPrime(unsigned long long int n) {
    if ( n == 2) {
        return true;
    }

    if ( n % 2 == 0) {
        return false;
    }

    float root = sqrt(n);
    for (int i = 3; i <= root; i += 2 ) {
        if ( n % i == 0) {
            return false;
        }
    }
    return true;
}

bool isNumber(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int main(int argc, char const *argv[])
{
    if ( argc != 3) {
        printUsage();
    } else {
        if ( argv[1] != "test" && argv[1] != "sieve" ) {
            printCommand();
        } else {
            
        }
        if ( isNumber(argv[1])) {
            unsigned long long int inputNumber;
            inputNumber = stoull(argv[1]);
            if ( inputNumber < 2) {
                printUsage();
            } else {
                if ( isPrime(inputNumber)) {
                    cout << inputNumber << " is a prime number" << endl;
                } else {
                    cout << inputNumber << " is NOT a prime number" << endl;
                }
            }
        } else {
            printUsage();
        }
    }
    return 0;
}
