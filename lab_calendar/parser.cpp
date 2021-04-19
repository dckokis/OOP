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
        Format.push_back(Range);
    } else if (RangeType == "year") {
        Format.push_back(Year);
    } else throw MyExceptionFormat(RangeType);

    return Format;
}

tuple<vector<OutputFormat>, vector<int>> Parser(ifstream FormatFile) {
    string RangeType;
    vector<int> Range;
    string Orient;
    string YearFormat;
    string Parsing;
    vector<string> Parsed;
//    if (!FormatFile) {
//        throw MyExceptionFile(FormatFileName);
//    }
    for (int n = 1; getline(FormatFile, Parsing); ++n) {
        for (size_t Pos = 0;;) {
            Pos = Parsing.find_first_not_of(" \t", Pos);
            if (Pos == string::npos)
                break;

            size_t Pos1 = Parsing.find_first_of(" \t", Pos);
            size_t len = (Pos1 == string::npos) ? string::npos : Pos1 - Pos;

            string Word(Parsing.substr(Pos, len));
            Parsed.push_back(Word);
            if (Pos1 == string::npos)
                break;
            Pos = Pos1;
        }
    }
    RangeType = Parsed[0];
    int rangePos;
    if (RangeType == "year") {
        Range.push_back(stoi(Parsed[1]));
        rangePos = 1;
    } else if (RangeType == "range") {
        Range.push_back(stoi(Parsed[1]));
        Range.push_back(stoi(Parsed[2]));
        Range.push_back(stoi(Parsed[3]));
        Range.push_back(stoi(Parsed[4]));
        rangePos = 4;
    } else throw MyExceptionFormat(RangeType);
    Orient = Parsed[rangePos + 1];
    YearFormat = Parsed[rangePos + 2];
    try {
        vector<OutputFormat> Format = DefineFormat(RangeType, Orient, YearFormat);
        return make_tuple(Format, Range);
    }
    catch (MyExceptionFormat myException) {
        myException.Msg();
    }
}