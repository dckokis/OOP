#pragma once

#include <string>
#include <string>
#include <iostream>

using namespace std;

class Month {
public:
    Month();
    inline int GetYear() const {
        return _year;
    }

    inline int GetMonth() const {
        return _month;
    }
private:
    static const std::string DayNames[7];
    static const std::string MonthNames[12];
    static const int DaysInMonth[12];

    int _year;
    int _month;
};