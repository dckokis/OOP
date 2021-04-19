#pragma once

#include <cstdio>
#include <string>
#include <vector>

enum OutputFormat {
    Vert = 0,
    Horiz,
    YearForEveryMonth,
    YearOnce,
    Range,
    Year
};


std::tuple<std::vector<OutputFormat>, std::vector<int>> Parser(const char FormatFileName[]);