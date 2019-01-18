
#include <iostream>

#include "json.hpp"

using namespace std;

using json = nlohmann::json;

int main() {
    // create an empty structure (null)
    json j;

    j["pi"] = 3.141;
    j["happy"] = true;

    cout << j.dump() << endl;
    
    json j2{
      {"pi", 3.141},
      {"happy", true}
    };

    cout << j2.dump() << endl;
}
