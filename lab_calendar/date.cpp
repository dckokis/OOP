#include "date.hpp"

Date::Date() {
}

void Date::setDate(int _day, int _month, int _year) {
    year = _year;
    month = _month;
    day = _day;
}

int Date::getYear() {
    return year;
}

int Date::getMonth() {
    return month;
}

int Date::getDay() {
    return day;
}
