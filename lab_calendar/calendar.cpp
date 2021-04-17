#include "calendar.hpp"
#include "myexception.hpp"
#include "parser.hpp"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

Calendar::Calendar() {
}

void Calendar::Run() {

    bool run = true;

    /********************************/
    ///*        Menu system       *///
    /********************************/

    while (run) {

        char UserCmd;
        char FileName[256];
        string file;
        cout
                << "\nD: Draw Calendar"
                << "\tQ: Quit"
                << "\nInput your command ";
        cin >> UserCmd;
        if (UserCmd >= 'a' && UserCmd <= 'z')
            UserCmd += ('A' - 'a');

        switch (UserCmd) {
            case 'D':
                cout << "\tInput format file";
                cin >> FileName;
                Draw(FileName);
            case 'Q':
                run = false;
                break;
            default:
                cout << "Invalid input." << endl;
                break;
        }
    }
}

void Calendar::Draw(const char FormatFileName[]) {
    try {
        auto [Format, Range] = Parser(FormatFileName);
    if (Range.size() == 4) {
        Calendar CalendarFirst, CalendarSecond;
        CalendarFirst.SetYear(Range[1]);
        CalendarSecond.SetYear(Range[3]);

    } else if (Range.size() == 1) {
        Calendar CalendarFirst;
        CalendarFirst.SetYear(Range[0]);

    }
    }
    catch (MyExceptionFile &myException) {
        myException.Msg();
    }
    catch (MyExceptionFormat &myException) {
        myException.Msg();
    }
}

void Calendar::NextMonth() {

}

void Calendar::PreviousMonth() {

}

void Calendar::SetYear(int _year) {
    year = _year;
}

