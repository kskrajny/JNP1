#ifndef JNP1_OPERATIONS_H
#define JNP1_OPERATIONS_H

#include <map>
#include <vector>

using namespace std;

// Rozkład jazdy jest mapą, która dla danego numeru kursu
// zwraca zbiór przystanków i czasów, w jakich kurs się na nich zatrzymuje
#define time_table map<string, map<string, int>>

//Zbiór biletów jest mapą, która dla danej nazwy biletu zwraca jego cenę i czas ważności
#define ticket_stock map<string, pair<double, int>>

bool addCourseToTimetable(time_table &timeTable, vector<string> course);

bool addTicketToStock(ticket_stock &ticketStock, vector<string> ticket);

pair<int, string> requestForTickets(time_table timeTable, ticket_stock ticketStock,
        vector<string> request);


#endif //JNP1_OPERATIONS_H
