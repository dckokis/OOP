#include "date.hpp"

Date::Date() {
}

const std::string Date::DayNames[7] = {
        "Sun",
        "Mon",
        "Tue",
        "Wen",
        "Thu",
        "Fri",
        "Sat"
};

const std::string Date::MonthNames[12] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
};

const int Date::MonthDays[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31,
};
