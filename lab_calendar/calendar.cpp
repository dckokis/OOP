#include "calendar.hpp"
#include "myexception.hpp"
#include "parser.hpp"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

Calendar::Calendar() {}

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

const std::string DayNames[1] = {"Sat Sun Mon Tue Wen Thu Fri"};

const std::string MonthNames[2] = {
        "         January                       February                        March                         April                          May                           June",
        "            July                         August                       September                      October                         November                   December"};

//const int MonthDays[12] = {
//        31, 28, 31, 30, 31, 30,
//        31, 31, 30, 31, 30, 31,
//};

enum Days {
    Sat = 0,
    Sun = 1,
    Mon = 2,
    Tue = 3,
    Wen = 4,
    Thu = 5,
    Fri = 6,
    Undefined = -1
};

enum MonthCode {
    January = 1,
    October = 1,
    May = 2,
    August = 3,
    February = 4,
    March = 4,
    November = 4,
    June = 5,
    December = 6,
    September = 6,
    April = 0,
    July = 0
};

enum YearIndent {
    c4 = 6,
    c3 = 0,
    c2 = 2,
    c1 = 4,
};

Days DefineDateDay(int Day, MonthCode Month, int Year, int Century) {
    int yearCode;
    switch (Century) {
        case c1:
            yearCode = (c1 + Year % 100 + (Year % 100) / 4);
            break;
        case c2:
            yearCode = (c2 + Year % 100 + (Year % 100) / 4);
            break;
        case c3:
            yearCode = (c3 + Year % 100 + (Year % 100) / 4);
            break;
        case c4:
            yearCode = (c4 + Year % 100 + (Year % 100) / 4);
            break;
        default:
            yearCode = 0;
            break;
    }
    int DefinedDayCode = (Day + Month + yearCode) % 7;
    Days DefinedDay;
    switch (DefinedDayCode) {
        case Sat:
            DefinedDay = Sat;
            break;
        case Sun:
            DefinedDay = Sun;
            break;
        case Mon:
            DefinedDay = Mon;
            break;
        case Tue:
            DefinedDay = Tue;
            break;
        case Wen:
            DefinedDay = Wen;
            break;
        case Thu:
            DefinedDay = Thu;
            break;
        case Fri:
            DefinedDay = Fri;
            break;
        default:
            DefinedDay = Undefined;
            break;
    }
    return DefinedDay;
}

string StrRepeat(const string &String, int n, const char *FillChar = " ") {
    string temp;
    for (int i = 0; i < n - 1; i++)
        temp.append(String + FillChar);
    temp.append(String);
    return temp;
}

void PrintYearHoriz(int Year, int StartMont = 1, int EndMonth = 12) {
    vector<Days> MonthStartDay = {DefineDateDay(1, January, Year, Year / 100),
                                  DefineDateDay(1, February, Year, Year / 100),
                                  DefineDateDay(1, March, Year, Year / 100),
                                  DefineDateDay(1, April, Year, Year / 100),
                                  DefineDateDay(1, May, Year, Year / 100),
                                  DefineDateDay(1, June, Year, Year / 100),
                                  DefineDateDay(1, July, Year, Year / 100),
                                  DefineDateDay(1, August, Year, Year / 100),
                                  DefineDateDay(1, September, Year, Year / 100),
                                  DefineDateDay(1, October, Year, Year / 100),
                                  DefineDateDay(1, November, Year, Year / 100),
                                  DefineDateDay(1, December, Year, Year / 100)};
    int MonthDays[12] = {
            31, 28, 31, 30, 31, 30,
            31, 31, 30, 31, 30, 31,
    };
    if (Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0)) {
        MonthDays[1] = 29;
    }
    // print year in the middle
    string Indent = StrRepeat(" ", 84, "");
    cout << Indent << Year << Indent << endl;
    // print first 6 moths
    cout << MonthNames[0] << endl;
    // print first line of week days
    string DaysLine = StrRepeat(*DayNames, 6, "   ");
    cout << DaysLine << endl;
    //print first line of each month
    vector<int> StopDate;
    for (int i = 0; i < 6; i++) {
        Days Start = MonthStartDay[i];
        int DaysLeft;
        switch (Start) {
            case Sat:
                Indent = StrRepeat(" ", 0, "");
                DaysLeft = 7;
                break;
            case Sun:
                Indent = StrRepeat(" ", 4, "");
                DaysLeft = 6;
                break;
            case Mon:
                Indent = StrRepeat(" ", 8, "");
                DaysLeft = 5;
                break;
            case Tue:
                Indent = StrRepeat(" ", 12, "");
                DaysLeft = 4;
                break;
            case Wen:
                Indent = StrRepeat(" ", 16, "");
                DaysLeft = 3;
                break;
            case Thu:
                Indent = StrRepeat(" ", 20, "");
                DaysLeft = 2;
                break;
            case Fri:
                Indent = StrRepeat(" ", 24, "");
                DaysLeft = 1;
                break;
            case Undefined:
                Indent = "UNDEFINED";
                DaysLeft = 0;
                break;
        }
        cout << Indent;
        int Date = 1;
        while (DaysLeft > 0) {
            cout << Date;
            Date += 1;
            DaysLeft -= 1;
        }
        cout << "     ";
        StopDate.push_back(Date);
    }
    cout << endl;
    //print next days till 28
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < 6; i++) {
            for (int j = 1; j < 7; j++) {
                string IndentDays;
                if ((StopDate[i] + j) % 10 > 0)
                    IndentDays = " ";
                cout << StopDate[i] + j << IndentDays << "  ";
            }
            cout << "     ";
            StopDate[i] = StopDate[i] + 7;
        }
        cout << endl;
    }
    //print last days
    for (int i = 0; i < 6; i++) {
        int j = 1;
        while (StopDate[i] <= MonthDays[i]) {
            cout << StopDate[i] + j << " " << "  ";
            j++;
        }
    }
    cout << endl;
}

void DrawVert() {

}

void DrawHoriz(Calendar CalendarFirst, Calendar CalendarSecond) {
    if (CalendarFirst.IsFull() && CalendarSecond.IsFull()) {
        int yearFirst = CalendarFirst.GetYear();
        int yearSecond = CalendarSecond.GetYear();
        int monthBegin = CalendarFirst.GetStartMonth();
        int monthEnd = CalendarSecond.GetEndMonth();;
//        Date curDay = Date();
//        curDay.setDate(1, monthBegin, yearFirst);
        if (yearFirst != yearSecond) {
            PrintYearHoriz(yearFirst, monthBegin, 12);
            for (int i = yearFirst + 1; i < yearSecond; i++) {
                PrintYearHoriz(i);
            }
            PrintYearHoriz(yearSecond, 1, monthEnd);
        }
    }
}

void Calendar::Draw(const char FormatFileName[]) {
    try {
        auto[Format, Range] = Parser(FormatFileName);
        OutputFormat Orient = Format[0];

        Calendar CalendarFirst, CalendarSecond;
        if (Range.size() == 4) {
            CalendarFirst.SetYear(Range[1]);
            CalendarFirst.SetStartMonth(Range[0]);
            CalendarSecond.SetYear(Range[3]);
            CalendarSecond.SetStartMonth(Range[2]);
        } else if (Range.size() == 1) {
            CalendarFirst.SetYear(Range[0]);
        }

        if (Orient == Vert) {
            DrawVert();
        } else if (Orient == Horiz) {
            DrawHoriz(CalendarFirst, CalendarSecond);
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
    SetFull();
}

void Calendar::SetFull() {
    isFull = true;
}

void Calendar::SetEmpty() {
    isFull = false;
}

bool Calendar::IsFull() {
    return isFull;
}

void Calendar::SetStartMonth(int Month) {
    startMonth = Month;
}

void Calendar::SetEndMonth(int Month) {
    endMonth = Month;
}

int Calendar::GetYear() {
    return year;
}

int Calendar::GetStartMonth() {
    return startMonth;
}

int Calendar::GetEndMonth() {
    return endMonth;
}

