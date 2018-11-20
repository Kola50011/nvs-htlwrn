#include <iostream>
#include <thread>
#include <string>
#include <iostream>
#include "InfInt.h"
#include "calc_factors.h"
#include <vector>
#include <future>

using namespace std;

bool contains(const char *argv[], int argc, string toCheck)
{
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == toCheck)
        {
            return true;
        }
    }
    return false;
}

bool isNumber(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

bool checkArgsValid(const char *argv[], int argc)
{
    for (int i = 1; i < argc; i++)
    {
        if (!isNumber(string(argv[i])))
        {
            cout << argv[i] << " is not a number!" << endl;
            return false;
        }
    }
    return true;
}

void printUsage()
{
    cout << "Usage: factoring [OPTION]... [NUMBER]..." << endl;
    cout << "Options:" << endl;
    cout << "\t--help\t\tdisplay this help and exit" << endl;
}

vector<vector<InfInt>> getFactorsAsync(vector<InfInt> numbers)
{
    vector<future<vector<InfInt>>> futs;
    for (auto &number : numbers)
    {
        futs.push_back(async(get_factors, number));
    }

    vector<vector<InfInt>> ret;
    for (auto &fut : futs)
    {
        ret.push_back(fut.get());
    }
    return ret;
}

void printNumbersToConsole(const char *argv[], int argc)
{
    vector<InfInt> numbers;
    for (int i = 1; i < argc; i++)
    {
        InfInt number = argv[i];
        numbers.push_back(number);
    }
    vector<vector<InfInt>> factors = getFactorsAsync(numbers);
    for (int i{}; i < numbers.size(); i++) {
        cout << numbers.at(i) << ":";
        for (auto number : factors.at(i))
        {
            cout << " " << number;
        }
        cout << endl;
    }
}

int main(int argc, const char *argv[])
{
    if (contains(argv, argc, "--help") || !checkArgsValid(argv, argc))
    {
        printUsage();
        return 1;
    }
    printNumbersToConsole(argv, argc);
}
