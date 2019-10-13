#include <iostream>
#include <bits/stdc++.h>
#include "operations.h"

using namespace std;

bool addCourseToTimetable(time_table timeTable, vector<string> course) {
    if (timeTable.find(course[0]) != timeTable.end()) {
        return false;
    }

    map<string, int> stops;

    for (int i = 1; i < course.size(); i += 2) {
        stops.insert(make_pair(course[i + 1], stoi(course[i])));
    }

    timeTable.insert(make_pair(course[0], stops));

    return true;
}

bool addTicketToStock(ticket_stock ticketStock, vector<string> ticket) {
    if (ticketStock.find(ticket[0]) != ticketStock.end()) {
        return false;
    }

    pair<double, int> new_ticket(stod(ticket[1]), stoi(ticket[2]));
    ticketStock.insert(make_pair(ticket[0], new_ticket));

    return true;
}

// Zwraca czas zatrzymania kursu na przystanku lub -1 jeśli nie istnieje przystanek lub kurs
// bądź dany kurs nie zatrzymuje się na danym przystanku
static int getTimeOrError(time_table timeTable, string stop, string course) {
    if (timeTable.find(course) == timeTable.end() ||
        timeTable.find(course)->second.find(stop) == timeTable.find(course)->second.end()) {
        return -1;
    }

    return timeTable.find(course)->second.find(stop)->second;
}

static string checkRequest(time_table timeTable, vector<string> request) {
    string res;

    if (getTimeOrError(timeTable, request[0], request[1]) < 0) {
        return "error";
    }

    for (int i = 2; i < request.size() - 1; i += 2) {
        int time1 = getTimeOrError(timeTable, request[i], request[i - 1]);
        int time2 = getTimeOrError(timeTable, request[i], request[i + 1]);

        if (time1 < 0 || time2 < 0 || time1 > time2) {
            return "error";
        }

        if (time1 < time2) {
            if (res.size()) {
                res = ":-(" + request[i];
            }
        }
    }

    if (getTimeOrError(timeTable, request.back(), request[request.size() - 2]) < 0) {
        return "error";
    }

    return res.size() ? res : "ok";
}

static int checkTimeOfTravel(int timeOfTravel,
        vector<ticket_stock::iterator> tickets) {
    int time = 0;

    for (ticket_stock::iterator it : tickets) {
        time += it->second.second;
    }

    if (time < timeOfTravel) {
        return 1;
    }

    return time == timeOfTravel ? 0 : -1;
}

static bool updateMinCostTickets(
        int timeOfTravel,
        pair<double, vector<string>> &min_tickets,
        vector<ticket_stock::iterator> tickets) {

    if (checkTimeOfTravel(timeOfTravel, tickets) > 0) {
        return true;
    }

    if (checkTimeOfTravel(timeOfTravel, tickets) < 0) {
        return false;
    }

    double cost = 0;

    for (ticket_stock::iterator it : tickets) {
        cost += it->second.first;
    }

    // TODO sprawdzić czy referencja działa
    if (cost < min_tickets.first) {
        vector<string> tickets_names;

        for (ticket_stock::iterator it : tickets) {
            tickets_names.push_back(it->first);
        }

        pair<double, vector<string>> new_min(cost, tickets_names);
        min_tickets = new_min;
    }

    return true;
}

// TODO zamienić string na pare <int, string> <koszt, bilety>
string requestForTickets(time_table timeTable, ticket_stock ticketStock,
                         vector<string> request) {
    string check = checkRequest(timeTable, request);

    if (check.compare("error") == 0) {
        return "error";
    }

    if (check.compare("ok") != 0) {
        return check;
    }

    int timeOfTravel =
            getTimeOrError(timeTable, request.back(),
                    request[request.size() - 2]) -
            getTimeOrError(timeTable, request[0], request[1]) + 1;

    pair<double, vector<string>> min_cost(DBL_MAX, {});
    ticket_stock::iterator it1, it2, it3;

    for (it1 = ticketStock.begin(); it1 != ticketStock.end(); ++it1) {
        if (updateMinCostTickets(timeOfTravel, min_cost, {it1}) > 0) {
            for (it2 = it1; it2 != ticketStock.end(); ++it2) {
                if (updateMinCostTickets(timeOfTravel, min_cost, {it1, it2}) > 0) {
                    for (it3 = it2; it3 != ticketStock.end(); ++it3) {
                        updateMinCostTickets(timeOfTravel, min_cost, {it1});
                    }
                }
            }
        }
    }

    if (min_cost.first == DBL_MAX) {
        return ":-|";
    }

    string res = to_string(min_cost.first);

    for (string single_ticket : min_cost.second) {
        res += single_ticket;
    }

    return res;
}

