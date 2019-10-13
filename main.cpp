#include <iostream>
#include <cstring>

#include "operations.h"
#include "parser.h"

using namespace std;

// write something, if it means expectations vector will be written by program,
// it will also convert hours(xx:xx) to minutes after 0:00 if they exists
int main() {
    string line;
    getline(cin, line);

    pair<int, vector<string>> checked_line = check_line(line);

    for(string x: checked_line.second){
        cout << "\n"+x;
    }

    cout << "\n";

    if (check_first(checked_line.second)){
        cout << "ok";
    } else {
        cout << "nieok";
    }

    //TODO przy zliczaniu 3. trzeba dodawać tutaj ceny (randomowa linijka z treści)

    return 0;
}
