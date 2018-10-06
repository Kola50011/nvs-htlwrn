#include <iostream>
#include <thread>
#include <string>
#include <vector>

using namespace std;

bool checkAllEqual(vector<string> input)
{
    string first = input[0];
    for (auto &elem : input)
        if (elem != first)
            return false;
    return true;
}

void printPeriod(string word)
{
    for (unsigned int i = 1; i < word.size(); i++)
    {
        if (word.size() % i != 0)
            continue;

        vector<string> toCheck;
        for (int x = 0; x * i < word.size(); x++)
            toCheck.push_back(word.substr(x * i, i));

        if (checkAllEqual(toCheck))
        {
            cout << i << " " << toCheck[0] << endl;
            return;
        }
    }
    cout << word.size() << " " << word << endl;
    return;
}

int main(int argc, char const *argv[])
{
    for (int i = 1; i < argc; i++)
        printPeriod(argv[i]);
}
