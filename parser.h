#ifndef JNP1_PARSER_H
#define JNP1_PARSER_H

// check if time increase, and stops doesn't repeat
bool check_first(vector<string> v);

// check if the line can meet expectations
pair<int, vector<string>> check_line(string line);

#endif //JNP1_PARSER_H
