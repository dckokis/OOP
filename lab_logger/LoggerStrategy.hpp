#pragma once
#include <xstring>

class LoggerStrategy {
public:
    virtual void write(const std::string &message) = 0;
};

class ConsoleLogger final : public LoggerStrategy {
public:
    void write(const std::string &message) override;
};

class SimpleStreamLogger final : public LoggerStrategy {
public:
    void write(const std::string &message) override;
};

class TimedStreamLogger final : public LoggerStrategy {
public:
    void write(const std::string &message) override;
};