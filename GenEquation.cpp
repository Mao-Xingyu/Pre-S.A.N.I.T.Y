#include "GenEquation.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
using namespace std;

string generateEquation(const string& userQuestion, const map<string, string>& formulas) {
    // Tokenize the user's input
    istringstream iss(userQuestion);
    vector<string> tokens(istream_iterator<string>{iss}, istream_iterator<string>());

    // Search for keywords in the tokens and map them to corresponding formulas
    for (const auto& token : tokens) {
        auto it = formulas.find(token);
        if (it != formulas.end()) {
            return it->second;
        }
    }
    return "No matching formula found.";
}