#pragma once
#include "LoggerStrategy.hpp"

class Logger {
public:
    void set_strategy(LoggerStrategy& strategy);

    void log_message(const std::string &message);
};
