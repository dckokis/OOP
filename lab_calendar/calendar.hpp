#pragma once

#include <cstdio>
#include <string>
#include <vector>
#include "parser.hpp"
#include "date.hpp"


class Calendar {
private:
    Arguments Args;
public:
    explicit Calendar(Arguments _args) : Args(_args) {} ;
    std::string DrawCalendar() noexcept;
};

std::string horizontalPrint(int monthBeg, int yearBeg, int monthEnd, int yearEnd, bool yearEveryMonth, bool yearOnce) noexcept;
std::string verticalPrint(int monthBeg, int yearBeg, int monthEnd, int yearEnd, bool yearEveryMonth, bool yearOnce) noexcept;