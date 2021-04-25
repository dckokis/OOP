#include "parser.hpp"
#include <vector>
#include <string>

using namespace std;

enum periods {
    month,
    year,
    range
};

enum features {
    vert = 0,
    horiz,
    year_for_every_month,
    year_once
};

vector<string> Periods = {"month", "year", "range"};
vector<string> Features = {"vert", "horiz", "year_for_every_month", "year_once"};

bool isPeriod(string &s) {
    return find(Periods.begin(), Periods.end(), s) != Periods.end();
}

bool isFeature(string &s) {
    return find(Features.begin(), Features.end(), s) != Features.end();
}

bool isNumber(const string &str) {
    for (char const &c : str) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

long int getMode(string &s) {
    auto it = find(Periods.begin(), Periods.end(), s);
    long int idx = distance(Periods.begin(), it);
    return idx;
}

long int getFeature(string &s) {
    auto it = find(Features.begin(), Features.end(), s);
    long int idx = distance(Features.begin(), it);
    return idx;
}


void readMonth(istream &file, Arguments *arg) {
    string temp;
    getline(file, temp, ' ');
    if (!isNumber(temp) || temp.empty()) {
        throw CalendarExceptionFormat("Month must be a number.");
    }
    int month = stoi(temp);
    if (month < 1 || month > 12) {
        throw CalendarExceptionFormat("Month must range from 1 to 12.");
    }
    arg->monthBegin = month;
    arg->monthEnd = month;
    getline(file, temp, ' ');
    if (!isNumber(temp) || temp.empty()) {
        throw CalendarExceptionFormat("Year must be a number.");
    }
    int year = stoi(temp);
    if (year <= 0) {
        throw CalendarExceptionFormat("Year must be greater than zero.");
    }
    arg->yearBegin = year;
    arg->yearEnd = year;
}

void readYear(istream &file, Arguments *arg) {
    string temp;
    getline(file, temp, ' ');
    if (!isNumber(temp) || temp.empty()) {
        throw CalendarExceptionFormat("Year must be a number.");
    }
    int year = stoi(temp);
    if (year <= 0) {
        throw CalendarExceptionFormat("Year must be greater than zero.");
    }
    arg->yearBegin = year;
    arg->yearEnd = year;
    arg->monthBegin = 1;
    arg->monthEnd = 12;
}

void readRange(istream &file, Arguments *arg) {
    string temp;
    getline(file, temp, ' ');
    if (!isNumber(temp) || temp.empty()) {
        throw CalendarExceptionFormat("Range must be a sequence of numbers.");
    }
    int monthBegin = stoi(temp);
    if (monthBegin < 1 || monthBegin > 12) {
        throw CalendarExceptionFormat("First month must range from 1 to 12.");
    }
    arg->monthBegin = monthBegin;
    getline(file, temp, ' ');
    if (!isNumber(temp) || temp.empty()) {
        throw CalendarExceptionFormat("Years in range must be numbers.");
    }
    int yearBegin = stoi(temp);
    if (yearBegin <= 0) {
        throw CalendarExceptionFormat("Year must be greater than zero.");
    }
    arg->yearBegin = yearBegin;
    getline(file, temp, ' ');
    if (!isNumber(temp) || temp.empty()) {
        throw CalendarExceptionFormat("Range must be a sequence of numbers.");
    }
    int monthEnd = stoi(temp);
    if (monthEnd < 1 || monthEnd > 12) {
        throw CalendarExceptionFormat("Second month must range from 1 to 12.");
    }
    arg->monthEnd = monthEnd;
    getline(file, temp, ' ');
    if (!isNumber(temp) || temp.empty()) {
        throw CalendarExceptionFormat("Years in range must be numbers.");
    }
    int yearEnd = stoi(temp);
    if (yearEnd < 1 || yearEnd < yearBegin) {
        throw CalendarExceptionFormat("Years in range must go in order.");
    }
    if (yearBegin == yearEnd && monthBegin > monthEnd) {
        throw CalendarExceptionFormat("Months in year must go in order.");
    }
    arg->yearEnd = yearEnd;
}

void readFeature(istream &file, Arguments *arg) {
    string temp;
    getline(file, temp, ' ');
    if (!(temp == "|")) {
        throw CalendarExceptionFormat("Period and Features must be separated by |");
    }
    getline(file, temp, ' ');
    if (!isFeature(temp) || (getFeature(temp) != vert && getFeature(temp) != horiz)) {
        throw CalendarExceptionFormat("You cannot use unknown features.");
    }
    if (getFeature(temp) == vert) {
        arg->vert = true;
        arg->horiz = false;
    }
    if (getFeature(temp) == horiz) {
        arg->vert = false;
        arg->horiz = true;
    }
    getline(file, temp, ' ');
    if (!isFeature(temp) || (getFeature(temp) != year_once && getFeature(temp) != year_for_every_month)) {
        throw CalendarExceptionFormat("You cannot use unknown features.");
    }
    if (getFeature(temp) == year_once) {
        arg->year_once = true;
        arg->year_for_every_month = false;
    }
    if (getFeature(temp) == year_for_every_month) {
        arg->year_for_every_month = true;
        arg->year_once = false;
    }
}

Arguments *parseFile(istream &file) {
    if (!file) {
        throw CalendarExceptionFile();
    }
    Arguments *arg = new Arguments;
    string temp;
    getline(file, temp, ' ');
    if(temp.empty() || !isPeriod(temp)){
        throw CalendarExceptionFormat("First argument must be period.");
    }
    switch (getMode(temp)) {
        case month:
            readMonth(file, arg);
            readFeature(file, arg);
            break;
        case year:
            readYear(file, arg);
            readFeature(file, arg);
            break;
        case range:
            readRange(file, arg);
            readFeature(file, arg);
            break;
        default:
            throw CalendarExceptionFormat("Unknown range.");
    }
    temp.clear();
    return arg;
}
