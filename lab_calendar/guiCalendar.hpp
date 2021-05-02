#pragma once
#include "date.hpp"
class guiCalendar final{
private:
    date begin;
    date end;
    bool vertical;
public:
    guiCalendar(date b, date e, bool orient = true): begin(b), end(e), vertical(orient) {};
    std::string Draw(bool yearEveryMonth, bool yearOnce);
};
