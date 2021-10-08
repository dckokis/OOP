#pragma once


class FilterIteratorExceptions : std::exception{
public:
    virtual void Message() {};
};

class OutOfRangeException : FilterIteratorExceptions {
public:
    inline void Message() override {
        std::cerr << "Can't dereference out of range filter iterator" << std::endl;
    }
};