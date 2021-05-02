#include "parser.hpp"

using namespace std;

vector<string> parser(istream &input) {
    vector<string> read;
    string line;
    while (getline(input, line))
        read.push_back(line);
    return read;
}
