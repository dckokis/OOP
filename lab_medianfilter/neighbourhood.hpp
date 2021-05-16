#pragma once

#include "BitmapPlusPlus.hpp"

class Neighbourhood {
private:
    size_t size;
    bmp::Pixel centralPixel;
    std::vector<bmp::Pixel> neighbouringPixels;
public:
    explicit Neighbourhood(size_t _size, const bmp::Pixel &_centralPixel,
                           const std::vector<bmp::Pixel> &allPixelsOfImage) noexcept(false);

    ~Neighbourhood() = default;

    [[nodiscard]] size_t getSize() const;

    [[nodiscard]] bmp::Pixel getCentralPixel() const;

    [[nodiscard]] std::vector<bmp::Pixel> getNeighbouringPixels() const;
};
