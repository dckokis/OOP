#pragma once

class FilterIteratorException : std::exception {
public:
    virtual void Message(){};
};

class EndIteratorDifference : FilterIteratorException {
public:
    inline void Message() override {
        std::cerr << "Can not difference .end() iterator!";
    }
};