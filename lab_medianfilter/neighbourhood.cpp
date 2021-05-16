#include "neighbourhood.hpp"
#include "mfExceptions.hpp"
#include "getIndexInVector.hpp"

using namespace std;
using namespace bmp;

Neighbourhood::Neighbourhood(size_t _size, const bmp::Pixel &_centralPixel,
                             const std::vector<bmp::Pixel> &allPixelsOfImage) {
    if (_size <= 0) {
        throw WrongFiltrationParamsExceptions();
    }
    size = _size;
    centralPixel = _centralPixel;
    auto centralPixelIdx = getIndexInVector(allPixelsOfImage, _centralPixel);
//    if (centralPixelIdx < 0) {
//        throw PixelExceptions(_centralPixel);
//    }
    vector<Pixel> neighbourhood (size * size);
    for (int idx = 0; idx < size * size; idx++) {
        neighbourhood[idx] = allPixelsOfImage[centralPixelIdx - (size * (size / 2) + (size / 2)) + idx];
    }
    neighbouringPixels = neighbourhood;
}

size_t Neighbourhood::getSize() const {
    return size;
}

bmp::Pixel Neighbourhood::getCentralPixel() const {
    return centralPixel;
}

std::vector<bmp::Pixel> Neighbourhood::getNeighbouringPixels() const {
    return neighbouringPixels;
}
