#include "getIndexInVector.hpp"
#include "pixelComparations.hpp"

size_t getIndexInVector(const std::vector<bmp::Pixel> &whereToFind, const bmp::Pixel &whatToFind) {
    const auto place = find_if(whereToFind.begin(), whereToFind.end(), compareWithControlPixel(whatToFind));
    if (place == whereToFind.end()) {
        return -1;
    }
    return place - whereToFind.begin();
}
