#include <iostream>
#include <cstring>
#include <regex>
#include <bits/stdc++.h>
#include <map>
#include <vector>

using namespace std;

// Rozkład jazdy jest mapą, która dla danego numeru kursu
// zwraca mapę przystanków na czas, w jakim kurs się na nim zatrzymuje
#define time_table map<string, map<string, int>>

// Zbiór biletów jest mapą, która dla danej nazwy biletu zwraca jego cenę i czas ważności
#define ticket_stock map<string, pair<double, int>>

// Funkcja sprawdza, czy podany w argumencie napis jest poprawnym poleceniem
// pierwsza wartość pary przyjmuje wartości całkowite od -1 do 3
// -1 - błędne polecenie, 0 - pusty napis, 1 - polecenie typu pierwszego, itd
// druga wartość pary, to vector napisów, gdy rozpoznano polecenie,
// lub pusty vector wpp
pair<int, vector<string>> checkLine(string line)
{
    regex first("([0-9]*)(\x20(([6-9]|1[0-9]|20):"
                "[0-5][0-9]|5:5[5-9]|21:([01][0-9]|2[01]))\x20"
                "([[:lower:]]|[[:upper:]]|_|\\^)+)*");
    regex second("([[:lower:]]|[[:upper:]]|\x20)+\x20"
                 "\\d+\\.\\d\\d\x20[1-9][0-9]*");
    regex third("\\?\x20(([[:lower:]]|[[:upper:]]|_|\\^)+"
                "\x20([0-9]*)\x20)*([[:lower:]]"
                "|[[:upper:]]|_|\\^)+");

    vector<string> v;
    pair<int, vector<string>> outcome;

    if (line == "")
    {
        outcome.first = 0;
        outcome.second = v;
        return outcome;
    }

    if (regex_match(line, first))
    {
        outcome.first = 1;
    }
    else
    {
        if (regex_match(line, second))
        {
            outcome.first = 2;
        }
        else
        {
            if (regex_match(line, third))
            {
                outcome.first = 3;
            }
            else
            {
                outcome.first = -1;
                outcome.second = v;
                return outcome;
            }
        }
    }

    line = line + " "; // ułatwia zapisanie pętli
    string word = "";
    int stage = 0;

    switch (outcome.first)
    {
    case 1:
        for (auto x: line)
        {
            if (x!=' ')
            {
                if (!stage == 0 || x != '0')
                {
                    word = word + x;
                    stage = 1;
                }
            }
            else
            {
                if (stage == 0 && word == "")
                {
                    word = "0";
                }
                v.push_back(word);
                word = "";
            }
        }
        if (v.size() < 3)
        {
            outcome.first = -1;
            v.clear();
            outcome.second = v;
        }
        break;
    case 2:
        for (auto x: line)
        {
            switch (stage)
            {
            case 0:
                if (int(x) < 48 || int(x) > 57)
                {
                    word = word + x;
                }
                else
                {
                    word.pop_back();
                    v.push_back(word);
                    word = "";
                    word = word + x;
                    stage = 1;
                }
                break;
            case 1:
                if (x != ' ')
                {
                    word = word + x;
                }
                else
                {
                    v.push_back(word);
                    word = "";
                }
                break;
            }
        }
        break;
    case 3:
        for (auto x: line)
        {
            if (x != ' ')
            {
                if (!stage == 0 || x != '0')
                {
                    word = word+x;
                    stage = 1;
                }
            }
            else
            {
                if (stage == 0 && word == "")
                {
                    word = "0";
                }
                v.push_back(word);
                word = "";
                stage = 0;
            }
        }
        if (v.size() < 4)
        {
            outcome.first = -1;
            v.clear();
            outcome.second = v;
        }
        break;

    }

    outcome.second = v;
    return outcome;
}

// Funkcja zwraca ilość minut, które minęły od 0:00
// do godziny zapisanej w stringu x
static int toMinutes(string x)
{
    x = x + ":";
    int sum = 0;
    int i = 0;
    int stage = 0;
    for (auto y: x)
    {
        if (y != ':')
        {
            i = i * 10 + int(y) - 48;
        }
        else
        {
            if (stage == 0)
            {
                sum = sum + i * 60;
                i = 0;
                stage = 1;
            }
            else
            {
                sum = sum + i;
            }
        }
    }
    return sum;
}

// Funkcja zwraca true, jeśli występujące w vectorze napisy
// symbolizujące godziny są uporządkowane rosnąco
// oraz przystanki się nie powtarzają
// false wpp
bool checkTimeAndStops(vector<string> v)
{
    regex time("[0-9]{1,2}:[0-9]{2}");
    vector<string> stops;
    int last = 0;
    int curr;

    for (auto x: v)
    {
        if (regex_match(x, time))
        {
            curr = toMinutes(x);
            if (last >= curr)
            {
                return false;
            }
            last = curr;
        }
        else
        {
            for (string y: stops)
            {
                if (x == y)
                {
                    return false;
                }
            }
            stops.push_back(x);
        }
    }

    return true;
}

// Funkcja wykonuje polecenie pierwszego rodzaju
// Zwraca true jeśli polecenie zakończyło się pomyślnie,
// false wpp
bool addCourseToTimetable(time_table &timeTable, vector<string> course)
{
    if (!checkTimeAndStops(course))
    {
        return false;
    }

    if (timeTable.find(course[0]) != timeTable.end())
    {
        return false;
    }

    map<string, int> stops;

    for (unsigned i = 1; i < course.size(); i += 2)
    {
        stops.insert(make_pair(course[i + 1], toMinutes(course[i])));
    }

    timeTable.insert(make_pair(course[0], stops));

    return true;
}

// Funkcja wykonuje polecenie drugiego rodzaju
// Zwraca true jeśli polecenie zakończyło się pomyślnie,
// false wpp
bool addTicketToStock(ticket_stock &ticketStock, vector<string> ticket)
{
    if (ticketStock.find(ticket[0]) != ticketStock.end())
    {
        return false;
    }

    pair<double, int> new_ticket(stod(ticket[1]), stoi(ticket[2]));
    ticketStock.insert(make_pair(ticket[0], new_ticket));

    return true;
}

// Zwraca czas zatrzymania kursu na przystanku lub -1 jeśli nie istnieje przystanek lub kurs
// bądź dany kurs nie zatrzymuje się na danym przystanku
static int getTimeOrError(time_table timeTable, string stop, string course)
{
    if (timeTable.find(course) == timeTable.end() ||
            timeTable.find(course)->second.find(stop) == timeTable.find(course)->second.end())
    {
        return -1;
    }

    return timeTable.find(course)->second.find(stop)->second;
}

// Funkcja sprawdza czy podana prośba o bilety jest poprawna.
// Jeśli nie jest, zwraca 'error',
// jeśli jest, ale na którymś przystanku trzeba czekać, zwraca
// ":-| nazwa_przystanku_gdzie_trzeba_czekać"
// wpp zwraca "ok"
static string checkRequest(time_table timeTable, vector<string> request)
{
    string res;

    int time1 = getTimeOrError(timeTable, request[1], request[2]);
    int time2 = getTimeOrError(timeTable, request[3], request[2]);

    if (time1 < 0 || time2 < 0 || time1 >= time2)
    {
        return "error";
    }

    if (getTimeOrError(timeTable, request[1], request[2]) < 0)
    {
        return "error";
    }

    for (unsigned i = 3; i < request.size() - 1; i += 2)
    {
        time1 = getTimeOrError(timeTable, request[i], request[i - 1]);
        time2 = getTimeOrError(timeTable, request[i], request[i + 1]);

        if (time1 < 0 || time2 < 0 || time1 > time2)
        {
            return "error";
        }

        if (request[i - 2] == request[i])
        {
            return "error";
        }

        if (time1 < time2)
        {
            if (res == "")
            {
                res = ":-( " + request[i];
            }
        }
    }

    if (request.back() == request[request.size() - 3])
    {
        return "error";
    }

    if (getTimeOrError(timeTable, request.back(),
                       request[request.size() - 2]) < 0)
    {
        return "error";
    }

    return res.size() ? res : "ok";
}

// Funkcja zwraca:
// true, jeśli łączny czas ważności biletów jest większy
// bądż równy czasowi podróży,
// false wpp
bool checkTimeOfTravel(int timeOfTravel,
                       vector<ticket_stock::iterator> tickets)
{
    int time = 0;

    for (ticket_stock::iterator it : tickets)
    {
        time += it->second.second;
    }

    if (time < timeOfTravel)
    {
        return false;
    }

    return true;
}

// Funkcja sprawdza, czy dany zestaw biletów pozwala na przejechanie
// całej podróży i jeśli tak, to uaktualnia minimalny koszt zakupu biletów
// oraz jego realizację.
// Zwraca:
// false, jeśli całkowity czas ważności biletów jest mniejszy niż
// czas podróży
// true wpp
bool updateMinCostTickets(
    int timeOfTravel,
    pair<double, vector<string>> &min_tickets,
    vector<ticket_stock::iterator> tickets)
{

    if (!checkTimeOfTravel(timeOfTravel, tickets))
    {
        return false;
    }

    double cost = 0;

    for (ticket_stock::iterator it : tickets)
    {
        cost += it->second.first;
    }

    if (cost < min_tickets.first)
    {
        vector<string> tickets_names;

        for (ticket_stock::iterator it : tickets)
        {
            tickets_names.push_back(it->first);
        }

        pair<double, vector<string>> new_min(cost, tickets_names);
        min_tickets = new_min;
    }

    return true;
}

// Funkcja wykonuje polecenie pierwszego rodzaju
// Zwraca:
// W przypadku znalezienia minimalnej realizacji zakupu
// <liczba potrzebnych biletów, bilety realizujące ten zakup>
// W przypadku, gdy na którymś przystanku trzeba czekać
// <0, ":-| nazwa_przystanku_gdzie_trzeba_czekać">
// W przypadku nie znalezienia biletów <0, ":-|">
// W przypadku błędnego wiersza <-1, "error">
pair<int, string> requestForTickets(time_table timeTable,
                                    ticket_stock ticketStock, vector<string> request)
{
    string check = checkRequest(timeTable, request);

    if (check.compare("error") == 0)
    {
        return make_pair(-1, "error");
    }

    if (check.compare("ok") != 0)
    {
        return make_pair(0, check);
    }

    int timeOfTravel =
        getTimeOrError(timeTable, request.back(),
                       request[request.size() - 2]) -
        getTimeOrError(timeTable, request[1], request[2]) + 1;

    pair<double, vector<string>> min_cost(DBL_MAX, {});
    ticket_stock::iterator it1, it2, it3;

    for (it1 = ticketStock.begin(); it1 != ticketStock.end(); ++it1)
    {
        if (!updateMinCostTickets(timeOfTravel, min_cost, {it1}))
        {
            for (it2 = it1; it2 != ticketStock.end(); ++it2)
            {
                if (!updateMinCostTickets(timeOfTravel,
                                          min_cost, {it1, it2}))
                {
                    for (it3 = it2; it3 != ticketStock.end(); ++it3)
                    {
                        updateMinCostTickets(timeOfTravel,
                                             min_cost, {it1, it2, it3});
                    }
                }
            }
        }
    }

    if (min_cost.first == DBL_MAX)
    {
        return make_pair(0, ":-|");
    }

    string res = "";

    for (string single_ticket : min_cost.second)
    {
        res += " " + single_ticket + ";";
    }

    res.pop_back();

    return make_pair(min_cost.second.size(), res);
}

void printError(const string &line, int line_no)
{
    string res = "Error in line ";

    res += to_string(line_no);
    res += ": ";
    res += line;

    cerr << res << endl;
}

int main()
{
    int line_no = 1;
    int sum = 0;
    string line;
    pair<int, vector<string>> data;
    time_table timeTable;
    ticket_stock ticketStock;

    while (getline(cin, line))
    {
        data = checkLine(line);

        switch (data.first)
        {
        case 0:
            break;
        case -1:
            printError(line, line_no);
            break;
        case 1:
            if (!addCourseToTimetable(timeTable, data.second))
            {
                printError(line, line_no);
            }
            break;
        case 2:
            if (!addTicketToStock(ticketStock, data.second))
            {
                printError(line, line_no);
            }
            break;
        case 3:
            pair<int, string> res = requestForTickets(timeTable, ticketStock, data.second);
            switch (res.first)
            {
            case -1:
                printError(line, line_no);
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

    cout << sum << endl;

    return 0;
}
