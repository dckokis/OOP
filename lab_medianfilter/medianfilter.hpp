#pragma once

#include "BitmapPlusPlus.hpp"
#include "neighbourhood.hpp"

class RGBPixelMedianFilter{
private:

public:
    //explicit RGBPixelMedianFilter(const Neighbourhood & _neighbourhood) : notFiltered(notFiltered){};
    static bmp::Pixel filter(Neighbourhood& notFiltered, size_t filtrationThreshold);
};

//class PixelMedianFilter {
//public:
//    void *filter(void *data, size_t filtrationThreshold);
//};