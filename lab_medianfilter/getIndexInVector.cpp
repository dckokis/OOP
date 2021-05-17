#include "getIndexInVector.hpp"
#include "pixelComparations.hpp"

size_t getIndexInVector(const std::vector<bmp::Pixel> &whereToFind, const bmp::Pixel &whatToFind) {
    const auto place = find_if(whereToFind.begin(), whereToFind.end(), compareWithControlPixel(whatToFind));
    if (place == whereToFind.end()) {
        return -1;
    }
    return place - whereToFind.begin();
}

size_t transform2Dinto1D(size_t X, size_t Y, size_t width) {
    return X + Y * width;
}
