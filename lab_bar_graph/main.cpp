#include "Histogram.hpp"
#include "readFile.hpp"
#include <fstream>

int main() {
    std::fstream source("input.txt") ;
    std::vector<int> input = parser(source);
    Histogram histogram = Histogram(input, 10, 1);
    std::map<int, int>::const_iterator current;
    current = histogram.begin();
    while (current != histogram.end()) {
        std::cout << "bin number: " << current->first << " size: " << current->second << std::endl;
        current++;
    }
    return 0;
}

