#pragma once

#include <string>

class date final{
public:
    date(int d, int m, int y) : day(d), month(m), year(y) {};
    int getYear();
    int getMonth();
    int getDay();

    void IncreaseMonth();
    void DecreaseMonth();
    static const std::string DayNames[7];
    static const std::string MonthNames[12];
    static const int MonthDays[12];
    //std::string ToString() const;
private:
    int year;
    int month;
    int day;
};
