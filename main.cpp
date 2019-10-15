#include <iostream>
#include <cstring>

#include "operations.h"
#include "parser.h"

using namespace std;

void printError(string line, int line_no) {
    string res = "Error in line";
    
    res += line_no;
    res += ":";
    res += line;
    
    cerr << result << endl;
}

int main() {
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
    
    cout << sum;

    return 0;
}
