#include "rangeCreate.hpp"
#include "numberOfDays.hpp"

bool IsRange(std::string word) {
    if (word == "range" || word == "month" || word == "year") {
        return true;
    }
    return false;
}

RangeType DefineRange(std::string word) {
    RangeType type{};
    if (word == "range")
        type = RANGE;
    else if (word == "year")
        type = YEAR;
    else if (word == "month")
        type = MONTH;
    return type;
}

bool IsNumber(std::string word) {
    for (auto ch: word) {
        if (!isdigit(ch))
            return false;
    }
    return true;
}

bool IsOrient(std::string word) {
    if (word == "vert" || word == "horiz")
        return true;
    return false;
}

bool IsYearType(std::string word) {
    if (word == "year_once" || word == "year_for_every_month")
        return true;
    return false;
}

Range CreateRange(std::vector<std::string> source) {
    Range range{};
    std::vector<int> period;
    for (auto line : source) {
        for (size_t notSpace = 0;;) {
            notSpace = line.find_first_not_of(" \t", notSpace);
            if (notSpace == std::string::npos)
                break;
            size_t isSpace = line.find_first_of(" \t", notSpace);
            size_t length = (isSpace == std::string::npos) ? std::string::npos : isSpace - notSpace;
            std::string word(line.substr(notSpace, length));
            if (IsRange(word)) {
                range.type = DefineRange(word);
            } else if (IsNumber(word)) {
                period.push_back(stoi(word));
            } else if (IsOrient(word)) {
                if (word == "vert")
                    range.orient = true;
                else
                    range.orient = false;
            } else if (IsYearType(word)) {
                if (word == "year_for_every_month")
                    range.yearEveryMonth = true;
                else if (word == "year_once")
                    range.yearOnce = true;
            } else if (word == "|"){
                notSpace = isSpace;
                continue;
            }
            else
                range.type = UNDEFINED;
            if (isSpace == std::string::npos)
                break;
            notSpace = isSpace;
        }
        if (range.type == RANGE) {
            range.begin[0] = 1;
            range.begin[1] = period[0];
            range.begin[2] = period[1];
            range.end[0] = numberOfDays(period[2], period[3]);
            range.end[1] = period[2];
            range.end[2] = period[3];
        } else if (range.type == YEAR) {
            range.begin[0] = 1;
            range.begin[1] = 1;
            range.begin[2] = period[0];
            range.end[0] = 31;
            range.end[1] = 12;
            range.end[2] = range.begin[2];
        } else if (range.type == MONTH) {
            range.begin[0] = 1;
            range.begin[1] = period[0];
            range.begin[2] = period[1];
            range.end[0] = numberOfDays(range.begin[1], range.begin[2]);
            range.end[1] = range.begin[1];
            range.end[2] = range.begin[2];
        }
        return range;
    }
    range.type = UNDEFINED;
    return range;
}