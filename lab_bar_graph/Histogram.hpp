#pragma once

#include <vector>
#include <map>
#include <iostream>

class Histogram {
private:
    std::map<int, int> Bins;
private:
    size_t binCount{};
    int max{};
    int min{};
public:
    Histogram() = default;

    explicit Histogram(std::vector<int> &input, int upperBoarder, int lowerBorder);

    Histogram(const Histogram &that) = default;

    bool operator==(const Histogram &that) const;

    std::map<int, int> &getBins();

    Histogram operator+(const Histogram &that) const;

    Histogram operator-(const Histogram &that) const;

    using iterator = std::map<int, int>::iterator;

    iterator begin();

    iterator end();
};