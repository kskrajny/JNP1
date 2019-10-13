#ifndef JNP1_PARSER_H
#define JNP1_PARSER_H

// check if time increase, and stops doesn't repeat
// TODO może zmienić nazwe tutaj bo niezbyt wiadomo co to jest check_first - może checkTimeAndStops
bool check_first(vector<string> v);

// check if the line can meet expectations
pair<int, vector<string>> check_line(string line);

#endif //JNP1_PARSER_H
