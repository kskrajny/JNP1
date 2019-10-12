#include "operations.h"

int convertTime(string time) {

}

void addCourseToTimetable(time_table timeTable, vector<string> course) {
    string num = course[1];
    //TODO trzeba sprawdzić czy ten kurs może już istnieje
    for (int i = 2; i < course.size(); i += 2) {
        timeTable.insert_or_assign(pair(course[i + 1], num), convertTime(course[i]));
    }
}

void addTicketToStock(ticket_stock ticketStock, vector<string> ticket) {
    ticketStock.push_back(tuple(ticket[1], stod(ticket[2]), stoi(ticket[3])));
}

string checkRequest(time_table timeTable, vector<string> request) {
    string nameOfWaitingStop;

    if (!timeTable.find(pair(request[1], request[2]))) {
        // Kurs 1 nie zatrzymuje się na przystanku 1
        // bądź nie istnieje kurs lub przystanek
        return ":-|";
    }

    for (int i = 3; i < request.size() - 1; i += 2) {
        if (!timeTable.find(pair(request[i], request[i - 1])) ||
            !timeTable.find(pair(request[i], request[i + 1]))) {
            // Kurs 1 nie zatrzymuje się na przystanku 1
            // bądź nie istnieje kurs lub przystanek
            return ":-|";
        }

        if (timeTable.find(pair(request[i], request[i - 1])) !=
            timeTable.find(pair(request[i], request[i + 1]))) {
            if (nameOfWaitingStop.size()) {
                return ":-|";
            }

            nameOfWaitingStop = request[i];
        }
    }

    if (nameOfWaitingStop.size()) {
        return ":-(" + nameOfWaitingStop;
    }

    return "";
}

string requestForTickets(time_table timeTable, ticket_stock ticketStock,
                         vector<string> request) {
    string check = checkRequest(timeTable, request);

    if (check.size()) {
        return check;
    }

    int timeOfTravel = timeTable.find(
            pair(request[request.size() - 1], request[request.size() - 2]))
            - timeTable.find(request[1], request[2]) + 1;


}

