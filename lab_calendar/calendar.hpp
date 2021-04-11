#pragma once

#include <cstdio>
#include <string>
#include <vector>

namespace {
    enum FORMAT {
        HORIZONTAL = 1,
        VERTICAL
    };
}

class Calendar {
public:
    Calendar();

    void DrawCalendarMonth();

    void DrawCalendarYear();

    void DrawCalendarRange();

    std::string ReadFile(FILE *input);

private:
    std::vector<std::string> StringParser(char *string);

    inline int Year() {
        return _year;
    }

    inline FORMAT format() {
        return _format;
    }

    FORMAT _format = HORIZONTAL;
    int _year;
};
