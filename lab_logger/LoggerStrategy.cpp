#include <iostream>
#include "LoggerStrategy.hpp"

void ConsoleLogger::write(const std::string &message) {
    std::cout << "LOG: " << message << std::endl;
}

void SimpleStreamLogger::write(const std::string &message) {

}

void TimedStreamLogger::write(const std::string &message) {

}
