#include "month.hpp"

Month::Month() {

}

const std::string Month::DayNames[7] = {
        "Sun",
        "Mon",
        "Tue",
        "Wen",
        "Thu",
        "Fri",
        "Sat"
};

const std::string Month::MonthNames[12] = {
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

const int Month::DaysInMonth[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31,
};
