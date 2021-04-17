#pragma once

#include <cstdio>
#include <string>
#include <vector>
#include "parser.hpp"
#include "date.hpp"


class Calendar {
public:
    Calendar();

    void Run(); //Main Menu system
    static void Draw(const char FormatFileName[]); //Main calendar draw loop
    void SetYear(int _year);
    void NextMonth(); // Print Next month
    void PreviousMonth(); //Print Previous Month
private:
    Date currentDate;
    int year;
};
