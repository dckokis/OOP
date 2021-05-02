#include <iostream>
#include <fstream>
#include "rangeCreate.hpp"
#include "guiCalendar.hpp"
#include "date.hpp"
#include "parser.hpp"
#include "daysCount.hpp"

int run(const char FileName[]) {
    std::ifstream inp(FileName);
    std::istream &input = inp;
    Range testRange = CreateRange(parser(inp));
    if (testRange.type == UNDEFINED) {
        std::cout << "Wrong input!!!" << std::endl;
        return 0;
    }
    date begin = date(testRange.begin[0], testRange.begin[1], testRange.begin[2]);
    date end = date(testRange.end[0], testRange.end[1], testRange.end[2]);
    guiCalendar testCal = guiCalendar(begin, end, testRange.orient);
    std::cout << testCal.Draw(testRange.yearEveryMonth, testRange.yearOnce);
    std::cout << std::endl;
    auto testDays = daysCounter(begin, end);
    for (auto days : testDays) {
        std:: cout << days << " ";
    }

    return 0;
}

int main(int argc, char* argv[]) {
    if (argv[1])
        run(argv[1]);
    else
        run("input.txt");

}
