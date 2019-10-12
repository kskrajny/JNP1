#ifndef JNP1_OPERATIONS_H
#define JNP1_OPERATIONS_H

#include <map>
#include <vector>

using namespace std;

/**
 * Rozkład jazdy jest mapą, która dla danej nazwy przystanku i numeru kursu
 * zwraca czas, w jakim ten kurs się na nim zatrzymuje
 */
#define time_table map<pair<string, string>, int>

/**
 * Zbiór biletów jest wektorem trójek <nazwa biletu, cena, czas ważności>
 */
#define ticket_stock vector<tuple<string, double, int>>

/**
 *
 * @param timeTable
 * @param course
 * @return Wartość true, gdy z powodzeniem dodaliśmy kurs, wartość false
 * w przypadku niepowodzenia, czyli gdy kurs o danym numerze już istnieje.
 */
bool addCourseToTimetable(time_table timeTable, vector<string> course);

void addTicketToStock(ticket_stock ticketStock, vector<string> ticket);

string requestForTickets(time_table timeTable, ticket_stock ticketStock,
        vector<string> request);


#endif //JNP1_OPERATIONS_H
