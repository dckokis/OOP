#include "date.hpp"

const std::string date::DayNames[7] = {
        "Sun",
        "Mon",
        "Tue",
        "Wen",
        "Thu",
        "Fri",
        "Sat"
};

const std::string date::MonthNames[12] = {
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

const int date::MonthDays[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31,
};

int date::getDay() {
    return day;
}

int date::getMonth() {
    return month;
}

int date::getYear() {
    return year;
}

void date::IncreaseMonth() {
    if (month < 12)
        ++month;
    else {
        month = 1;
        ++year;
    }
}

void date::DecreaseMonth() {
    if (month > 1)
        --month;
    else {
        month = 12;
        --year;
    }
}