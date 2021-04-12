#pragma once

#include <string>
#include <vector>

class Parser {
public:
    std::string ReadFile(std::string input);
    std::vector<std::string> StringParser(std::string string);
    inline std::vector<std::string> GetProcessedString() const{
        return ProcessedString;
    }
private:
    std::vector<std::string> ProcessedString;
};
