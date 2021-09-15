#include "readFile.hpp"
#include <string>

std::vector<int> parser(std::istream &inp) {
    int number;
    std::vector <int> numbers;
    while (inp >> number)
        numbers.push_back(number);
    return numbers;
}
