#pragma once

#include <exception>


class HistogramExceptions : std::exception {
protected:
    virtual void Message() = 0;
};

class ArithmeticException : HistogramExceptions {
public:
    inline void Message() override {
        std::cerr << "To perform arithmetic operations, the main parameters of histograms must match." << std::endl;
    }
};

class CreationException : HistogramExceptions {
public:
    inline void Message() override {
        std::cerr << "To create histogram input correct parameters." << std::endl;
    }
};