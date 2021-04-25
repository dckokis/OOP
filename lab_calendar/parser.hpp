#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "calendar_exception.hpp"

typedef struct Arguments {
    int monthBegin;
    int yearBegin;
    int monthEnd;
    int yearEnd;

    bool vert;
    bool horiz;
    bool year_for_every_month;
    bool year_once;
} Arguments;

Arguments *parseFile(std::stringstream &file) noexcept(false);
