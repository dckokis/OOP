#pragma once
#include <string>
#include <vector>

enum RangeType {
    RANGE,
    YEAR,
    MONTH,
    UNDEFINED
};


struct Range {
    RangeType type;
    int begin[3];
    int end[3];
    bool orient; //true - vertical, false - horizontal
    bool yearEveryMonth = false;
    bool yearOnce = false;
};

Range CreateRange(std::vector<std::string> source);