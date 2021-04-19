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

    void setDate(int _day, int _month, int _year);

    void IncreaseMonth();

    void DecreaseMonth();

    string ToString() const;

private:
    int year;
    int month;
    int day;
};