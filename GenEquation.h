#pragma once
#ifndef _GENEQUATION_H_
#define _GENEQUATION_H_

// C++ standard library and STL headers
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
using namespace std;

//any common shared function calls
string generateEquation(const string& userQuestion, const map<string, string>& formulas);

#endif