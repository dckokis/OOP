#pragma once

#include <utility>
#include <exception>
#include <iostream>
#include "BitmapPlusPlus.hpp"

class MedianFilterExceptions : std::exception {
protected:
    virtual void Message() = 0;
};

class WrongInputExceptions : MedianFilterExceptions {
public:
    inline void Message() override {
        std::cerr << "Wrong input data! Check your input." << std::endl;
    }
};

class WrongFiltrationParamsExceptions: MedianFilterExceptions {
public:
    inline void Message() override {
        std::cerr << "Wrong filtration params! Check your neighbour size and filtration threshold." << std::endl;
    }
};

class PixelExceptions : MedianFilterExceptions {
public:
    explicit PixelExceptions(const bmp::Pixel & _badPixel) : badPixel(_badPixel) {};
    inline void  Message() override {};
    inline bmp::Pixel returnBadPixel(){
        return badPixel;
    }
private:
    bmp::Pixel badPixel;
};