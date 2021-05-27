#pragma once

#include "date.hpp"

class guiCalendar final {
private:
    bool orient; //true - vert, false-horiz
public:
    guiCalendar(bool orient = true) : orient(orient) {};

    std::string Draw(bool yearEveryMonth, bool yearOnce, Date beginDate, Date endDate);
};
