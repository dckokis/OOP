#pragma once

#include <vector>
#include <map>
#include <iostream>

class Histogram {
private:
    std::map<int, int> Bins;
private:
    size_t binCount;
    int max;
    int min;
public:
    Histogram();

    explicit Histogram(const std::vector<int> &input, int upperBoarder, int lowerBorder);//сделать константный вектор

    Histogram(const Histogram &that) = default;

    bool operator==(const Histogram &that) const;

    Histogram operator+(const Histogram &that) const;

    Histogram operator-(const Histogram &that) const;

    using iterator = std::map<int, int>::iterator;
    using const_iterator = std::map<int, int>::const_iterator;

    iterator begin();

    iterator end();

    const_iterator cbegin();

    const_iterator cend();
};