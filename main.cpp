#include <iostream>
#include <cstring>

#include "operations.h"
#include "parser.h"

using namespace std;

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
                cout << requestForTickets(timeTable, ticketStock, data).second << endl;
        }
    }
}

// write something, if it means expectations vector will be written by program,
// it will also convert hours(xx:xx) to minutes after 0:00 if they exists
int main() {
    //testOperations();

    int line_no = 1;
    int sum = 0;
    string line;
    pair<int, vector<string>> data;
    time_table timeTable;
    ticket_stock ticketStock;

    while (getline(cin, line)) {
        data = checkLine(line);

        switch (data.first) {
            case 0:
                break;
            case -1:
                cerr << line_no << " " + line << endl;
                break;
            case 1:
                if (!addCourseToTimetable(timeTable, data.second)) {
                    cerr << line_no << " " + line << endl;
                }
                break;
            case 2:
                if (!addTicketToStock(ticketStock, data.second)) {
                    cerr << line_no << " " + line << endl;
                }
                break;
            case 3:
                pair<int, string> res = requestForTickets(timeTable, ticketStock, data.second);
                switch (res.first) {
                    case -1:
                        cerr << line_no << " " + line << endl;
                        break;
                    case 0:
                        cout << res.second << endl;
                        break;
                    default:
                        sum += res.first;
                        cout << "!" + res.second << endl;
                }
                break;
        }

        line_no++;
    }


    //TODO przy zliczaniu 3. trzeba dodawać tutaj ceny (randomowa linijka z treści)

    return 0;
}
