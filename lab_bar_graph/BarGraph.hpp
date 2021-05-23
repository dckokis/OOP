#pragma once
#include "Bin.hpp"
#include <vector>
#include <map>
#include <iostream>

class BarGraph {
private:
    std::map<int, Bin> Bins;
private:
    size_t binCount;
    int max;
    int min;
public:
    BarGraph(std::vector<int> & input);
    //BarGraph(std::istream & input);
    bool operator==(const BarGraph & that) const;
    BarGraph operator+(const BarGraph & that) const;
    BarGraph operator-(const BarGraph & that) const;
    void AddBin(Bin newBin);
    size_t GetSize();
};

