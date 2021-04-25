#include <iostream>
#include <fstream>
#include "calendar.hpp"

int run(const char FileName[]) {
    std::stringstream ss;
    std::ifstream inp(FileName);
    ss << inp.rdbuf();
    try {
        Calendar test = Calendar(*parseFile(ss));
        std::cout << test.DrawCalendar();
    }
    catch (CalendarExceptionFormat &calendarExceptionFormat) {
        calendarExceptionFormat.Msg();
    }
    catch (CalendarExceptionFile &calendarExceptionFile) {
        calendarExceptionFile.Msg();
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argv[1])
        run(argv[1]);
    else
        run("input.txt");
}
