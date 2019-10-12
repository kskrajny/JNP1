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

    for(string x: check_line(line).second){
        cout << "\n"+x;
    }

    cout << "\n";

    if (check_first(check_line(line).second)){
        cout << "ok";
    } else {
        cout << "nieok";
    }

    return 0;
}
