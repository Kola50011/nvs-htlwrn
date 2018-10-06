
#include <iostream>
#include <thread>

using namespace std;

void append()
{
    std::string str;
    std::string str2 = "Writing ";
    std::string str3 = "print 10 and then 5 more";

    // used in the same order as described above:
    str.append(str2);                         // "Writing "
    str.append(str3, 6, 3);                   // "10 "
    str.append("dots are cool", 5);           // "dots "
    str.append("here: ");                     // "here: "
    str.append(10u, '.');                     // ".........."
    str.append(str3.begin() + 8, str3.end()); // " and then 5 more"

    std::cout << str << '\n';
}

void compare()
{
    std::string str1("green apple");
    std::string str2("red apple");

    if (str1.compare(str2) != 0)
        std::cout << str1 << " is not " << str2 << '\n';

    if (str1.compare(6, 5, "apple") == 0)
        std::cout << "still, " << str1 << " is an apple\n";

    if (str2.compare(str2.size() - 5, 5, "apple") == 0)
        std::cout << "and " << str2 << " is also an apple\n";

    if (str1.compare(6, 5, str2, 4, 5) == 0)
        std::cout << "therefore, both are apples\n";
}

void copy()
{
    char buffer[20];
    std::string str("Test string...");
    std::size_t length = str.copy(buffer, 6, 5);
    buffer[length] = '\0';
    std::cout << "buffer contains: " << buffer << '\n';
}

void find()
{
    std::string str("There are two needles in this haystack with needles.");
    std::string str2("needle");

    // different member versions of find in the same order as above:
    std::size_t found = str.find(str2);
    if (found != std::string::npos)
        std::cout << "first 'needle' found at: " << found << '\n';

    found = str.find("needles are small", found + 1, 6);
    if (found != std::string::npos)
        std::cout << "second 'needle' found at: " << found << '\n';

    found = str.find("haystack");
    if (found != std::string::npos)
        std::cout << "'haystack' also found at: " << found << '\n';

    found = str.find('.');
    if (found != std::string::npos)
        std::cout << "Period found at: " << found << '\n';

    // let's replace the first needle:
    str.replace(str.find(str2), str2.length(), "preposition");
    std::cout << str << '\n';
}

void insert()
{
    std::string str = "to be question";
    std::string str2 = "the ";
    std::string str3 = "or not to be";
    std::string::iterator it;

    // used in the same order as described above:
    str.insert(6, str2);                                // to be (the )question
    str.insert(6, str3, 3, 4);                          // to be (not )the question
    str.insert(10, "that is cool", 8);                  // to be not (that is )the question
    str.insert(10, "to be ");                           // to be not (to be )that is the question
    str.insert(15, 1, ':');                             // to be not to be(:) that is the question
    it = str.insert(str.begin() + 5, ',');              // to be(,) not to be: that is the question
    str.insert(str.end(), 3, '.');                      // to be, not to be: that is the question(...)
    str.insert(it + 2, str3.begin(), str3.begin() + 3); // (or )

    std::cout << str << '\n';
}

void replace()
{
    std::string base = "this is a test string.";
    std::string str2 = "n example";
    std::string str3 = "sample phrase";
    std::string str4 = "useful.";

    // replace signatures used in the same order as described above:

    // Using positions:                 0123456789*123456789*12345
    std::string str = base;           // "this is a test string."
    str.replace(9, 5, str2);          // "this is an example string." (1)
    str.replace(19, 6, str3, 7, 6);   // "this is an example phrase." (2)
    str.replace(8, 10, "just a");     // "this is just a phrase."     (3)
    str.replace(8, 6, "a shorty", 7); // "this is a short phrase."    (4)
    str.replace(22, 1, 3, '!');       // "this is a short phrase!!!"  (5)

    // Using iterators:                                               0123456789*123456789*
    str.replace(str.begin(), str.end() - 3, str3);                      // "sample phrase!!!"      (1)
    str.replace(str.begin(), str.begin() + 6, "replace");               // "replace phrase!!!"     (3)
    str.replace(str.begin() + 8, str.begin() + 14, "is coolness", 7);   // "replace is cool!!!"    (4)
    str.replace(str.begin() + 12, str.end() - 4, 4, 'o');               // "replace is cooool!!!"  (5)
    str.replace(str.begin() + 11, str.end(), str4.begin(), str4.end()); // "replace is useful."    (6)
    std::cout << str << '\n';
}

void substr()
{
    std::string str = "We think in generalities, but we live in details.";
    // (quoting Alfred N. Whitehead)

    std::string str2 = str.substr(3, 5); // "think"

    std::size_t pos = str.find("live"); // position of "live" in str

    std::string str3 = str.substr(pos); // get from "live" to the end

    std::cout << str2 << ' ' << str3 << '\n';
}

int main()
{
    cout << "append" << endl;
    append();
    cout << endl;

    cout << "compare" << endl;
    compare();
    cout << endl;

    cout << "copy" << endl;
    copy();
    cout << endl;

    cout << "find" << endl;
    find();
    cout << endl;

    cout << "insert" << endl;
    insert();
    cout << endl;

    cout << "replace" << endl;
    replace();
    cout << endl;

    cout << "substr" << endl;
    substr();
    cout << endl;
}
