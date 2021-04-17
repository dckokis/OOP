#include "parser.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "myexception.hpp"

using namespace std;

vector<OutputFormat> DefineFormat(const string &RangeType, const string &Orient, const string &YearFormat) {
    vector<OutputFormat> Format;

    if (Orient == "vert") {
        Format.push_back(Vert);
    } else if (Orient == "horiz") {
        Format.push_back(Horiz);
    } else throw MyExceptionFormat(Orient);

    if (YearFormat == "year_for_every_month") {
        Format.push_back(YearForEveryMonth);
    } else if (YearFormat == "year_once") {
        Format.push_back(YearOnce);
    } else throw MyExceptionFormat(YearFormat);

    if (RangeType == "range") {
        Format.push_back(YearRange);
    } else if (RangeType == "year") {
        Format.push_back(Year);
    } else throw MyExceptionFormat(RangeType);

    return Format;
}

tuple<vector<OutputFormat>, vector<int>> Parser(const char FormatFileName[]) {
    string RangeType;
    vector<int> Range;
    string Orient;
    string YearFormat;
    ifstream FormatFile(FormatFileName);
    if (!FormatFile) {
        throw MyExceptionFile(FormatFileName);
    }
    if (FormatFile >> RangeType) {
        int var;
        while (FormatFile >> var) {
            Range.push_back(var);
        }
        if (Range.size() > 4) {
            throw MyExceptionFormat();
        }
    } else throw MyExceptionFormat();

    if (FormatFile >> Orient) {
    } else throw MyExceptionFormat();

    if (FormatFile >> YearFormat) {
    } else throw MyExceptionFormat();
    try {
        vector<OutputFormat> Format = DefineFormat(RangeType,Orient, YearFormat);
        return make_tuple(Format, Range);
    }
    catch (MyExceptionFormat myException) {
        myException.Msg();
    }
}