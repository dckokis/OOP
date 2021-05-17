#pragma once

#include "BitmapPlusPlus.hpp"

size_t getIndexInVector(const std::vector<bmp::Pixel> &whereToFind, const bmp::Pixel &whatToFind);
size_t transform2Dinto1D(size_t X, size_t Y, size_t width);
