#pragma once

#include <string>
#include <string>
#include <iostream>


class Date {
public:
    Date();

    int getYear(); //get the current year
    int getMonth(); //get the current month
    int getDay(); //get the current day

    std::string getMonthString();
    std::string getDayString();

private:
    int year;
    int month;
    int day;
};