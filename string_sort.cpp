/*
 *      String reverse sorter
 *      Author: AlexIII
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include "custom_string.h"

using namespace std;

int main() {
    vector<Custom::String> strings;

    // Read input lines
    while(cin) {
        Custom::String str;
        cin >> str;
        if(str.empty()) break;
        if(str.back() != '\n') str += "\n";
        strings.push_back(move(str));
    }

    // Sort lines
    sort(strings.begin(), strings.end(), [](const auto& a, const auto& b) {
        return a.asLower() > b.asLower();
    });


    // Output lines
    for(auto& s: strings) {
        cout << s;
    }

    return 0;
}
