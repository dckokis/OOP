#pragma once

#include <string>
#include <string>
#include <iostream>

using namespace std;

class Date {
public:
    Date();

    int getYear(); //get the current year
    int getMonth(); //get the current month
    int getDay(); //get the current day

    void setDate(int, int, int);

    void IncreaseMonth();

    void DecreaseMonth();

    static const std::string DayNames[7];
    static const std::string MonthNames[12];
    static const int MonthDays[12];
    string ToString() const;

private:
    int year;
    int month;
    int day;

};