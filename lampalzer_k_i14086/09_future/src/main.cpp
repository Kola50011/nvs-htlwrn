#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#pragma GCC diagnostic ignored "-Wsign-compare"
#include "InfInt.h"
#pragma GCC diagnostic pop

#include <iostream>
#include <thread>
#include <string>
#include <iostream>
#include "calc_factors.h"
#include <vector>
#include <future>

using namespace std;

vector<string> argsToVector(int argc, const char *argv[])
{
    vector<string> strings;
    for (int i {1}; i < argc; i++) {
        strings.push_back(argv[i]);
    }
    return strings;
}

bool contains(vector<string>& args, string toCheck)
{
    for (auto arg : args) {
        if (arg == toCheck) {
            return true;
        }
    }
    return false;
}

void removeFromArgs(vector<string>& args, string toRemove)
{
    for (unsigned int i{}; i < args.size(); i++)
    {
        if (args.at(i) == toRemove)
        {
            args.erase(args.begin() + i);
        }
    }
}

bool isNumber(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

bool checkArgsValid(vector<string> &args)
{
    for (auto arg : args)
    {
        if (!isNumber(arg))
        {
            cout << arg << " is not a number!" << endl;
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

vector<shared_future<vector<InfInt>>> getFactorsAsync(vector<InfInt> numbers, launch lnch)
{
    vector<shared_future<vector<InfInt>>> futs;
    for (auto &number : numbers)
    {
        futs.push_back(async(lnch, get_factors, number));
    }

    return futs;
}

void printNumbersToConsole(vector<InfInt> &numbers, vector<shared_future<vector<InfInt>>> factorFuts)
{
    for (unsigned int i{}; i < numbers.size(); i++)
    {
        cout << numbers.at(i) << ":";
        for (auto number : factorFuts.at(i).get())
        {
            cout << " " << number;
        }
        cout << endl;
    }
}

void checkFactors(vector<InfInt> &numbers, vector<shared_future<vector<InfInt>>> factorFuts)
{
    for (unsigned int i{}; i < numbers.size(); i++)
    {
        InfInt prod = 1;
        for (auto number : factorFuts.at(i).get())
        {
            prod *= number;
        }
        if ( prod != numbers.at(i) ) {
            cerr << "Factoring FAILED for: " << numbers.at(i) << endl;
        }
    }
}

void handleNumbers(vector<string> &args, launch lnch)
{
    vector<InfInt> numbers;
    for (auto arg : args) {
        InfInt number = arg;
        numbers.push_back(number);
    }

    auto factorsFuture = async(getFactorsAsync, numbers, lnch);
    vector<shared_future<vector<InfInt>>> factorFuts = factorsFuture.get();


    thread printThread{printNumbersToConsole, ref(numbers), factorFuts};

    auto start = chrono::system_clock::now();
    thread checkThread{checkFactors, ref(numbers), factorFuts};
    checkThread.join();
    auto duration = chrono::duration_cast<chrono::milliseconds>(std::chrono::system_clock::now() - start);
    cout << "Time elapsed used for factoring: " << duration.count() << "ms" << endl;

    printThread.join();
}

int main(int argc, const char *argv[])
{
    launch lnch = launch::deferred;

    vector<string> args = argsToVector(argc, argv);

    if (contains(args, "--async"))
    {
        lnch = launch::async;
        removeFromArgs(args, "--async");
    }
    if (contains(args, "--help") || !checkArgsValid(args))
    {
        printUsage();
        return 1;
    }
    handleNumbers(args, lnch);
}
