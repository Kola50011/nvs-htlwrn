#include <iostream>
#include <unordered_map>

using namespace std;

int main(int argc, char const *argv[])
{
    unordered_map<char, int> romanChars({{'I', 1},
                                         {'V', 5},
                                         {'X', 10},
                                         {'L', 50},
                                         {'C', 100},
                                         {'D', 500},
                                         {'M', 1000}});

    string romanNumber;

    cout << "roman number: ";
    cin >> romanNumber;

    int sum = 0;
    int lastNumber = 0;

    for (int i = 0; i < romanNumber.length(); i++)
    {
        int currentNumber = romanChars[romanNumber[i]];

        if (currentNumber == 0)
        {
            cout << "invalid roman number!" << endl;
            return 0;
        }

        if (lastNumber < currentNumber)
        {
            sum -= lastNumber;
            sum += currentNumber - lastNumber;
        }
        else
        {
            sum += currentNumber;
        }
        lastNumber = currentNumber;
    }

    cout << sum << endl;
    return 0;
}
