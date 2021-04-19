#pragma once

#include <cstdio>
#include <string>
#include <vector>
#include "parser.hpp"
#include "date.hpp"


class Calendar {
private:
    bool isFull = false;
    int startMonth = 1;
    int endMonth = 12;
    Date currentDate;
    int year;
public:
    Calendar();

    void Run(); //Main Menu system
    static void Draw(const char FormatFileName[]); //Main calendar draw loop
    static void Draw(string Format);
    void SetYear(int _year);
    int GetYear();
    void SetStartMonth(int Month);
    int GetStartMonth();
    int GetEndMonth();
    void SetEndMonth(int Month);
    void SetFull();
    void SetEmpty();
    bool IsFull();
    void NextMonth(); // Print Next month
    void PreviousMonth(); //Print Previous Month

};
