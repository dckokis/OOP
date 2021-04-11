#pragma once

#include <string>
#include <string>
#include <iostream>

using namespace std;

class Month {
public:
    Month();

private:
    static const std::string DayNames[7];
    static const std::string MonthNames[12];
    static const int DaysInMonth[12];

    inline int GetYear() {
        return _year;
    }

    inline int GetMonth() {
        return _month;
    }

    int _year;
    int _month;
};