#include <iostream>
#include <cstring>

#include "operations.h"
#include "parser.h"

using namespace std;

void testParser() {
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
}

void testOperations() {
    int n, m;
    string s;
    time_table timeTable;
    ticket_stock ticketStock;

    for (int i = 0; i < 3; i++) {
        cin >> n;

        for (int j = 0; j < n; j++) {
            vector<string> data;
            cin >> m;
            for (int k = 0; k < m; k++) {
                cin >> s;
                data.push_back(s);
            }

            if (i == 0)
                cout << (addCourseToTimetable(timeTable, data) ? "ok" : "no") << endl;
            if (i == 1)
                cout << (addTicketToStock(ticketStock, data) ? "ok" : "no") << endl;
            if (i == 2)
                cout << requestForTickets(timeTable, ticketStock, data) << endl;
        }
    }
}

// write something, if it means expectations vector will be written by program,
// it will also convert hours(xx:xx) to minutes after 0:00 if they exists
int main() {
    //testParser();

    testOperations();

    //TODO przy zliczaniu 3. trzeba dodawać tutaj ceny (randomowa linijka z treści)

    return 0;
}
