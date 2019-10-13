#ifndef JNP1_PARSER_H
#define JNP1_PARSER_H

#include <iostream>
#include <vector>

using namespace std;

// check if time increase, and stops doesn't repeat
bool checkTimeAndStops(vector<string> v);

// check if the line can meet expectations
pair<int, vector<string>> checkLine(string line);

#endif //JNP1_PARSER_H
