#pragma once

#include <string>
#include <iostream>
#include <utility>

class MyException: std::exception{
protected:
    virtual void Msg() = 0;
};

class MyExceptionFile: MyException {
private:
    std::string FileName;
public:
    explicit MyExceptionFile(const char FormatFileName[]) : FileName(FormatFileName) {};
    inline void Msg() override {
        std::cerr << "Your file" << FileName << "could not be opened" << endl;
    }
};

class MyExceptionFormat: MyException {
private:
    std::string Format;
public:
    explicit MyExceptionFormat(std::string  WrongFormat = "Undefined"): Format(std::move(WrongFormat)) {};
    inline void Msg() override {
        std::cerr << "Wrong output format:" << Format << ". Choose supported format." << endl;
    }
};