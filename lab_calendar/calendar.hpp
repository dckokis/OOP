#pragma once

#include <cstdio>
#include <string>
#include <vector>
#include "parser.hpp"

namespace {
    enum FORMAT {
        HORIZONTAL = 1,
        VERTICAL
    };
}

class Calendar {
public:
    Calendar(std::vector<std::string> input);

    void Draw(std::string input);

    [[nodiscard]] inline int Year() const {
        return _year;
    }

    [[nodiscard]] inline FORMAT Format() const{
        return _format;
    }
private:
    void DrawCalendarMonth(std::string input);

    void DrawCalendarYear(std::string input);

    void DrawCalendarRange(std::string input);

    FORMAT _format = HORIZONTAL;
    int _year;
};
