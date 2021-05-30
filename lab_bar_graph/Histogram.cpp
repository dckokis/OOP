#include "Histogram.hpp"
#include "histogramExceptions.hpp"
#include <algorithm>

using namespace std;

Histogram::Histogram(const std::vector<int> &input, int upperBoarder, int lowerBorder) {
    if (upperBoarder < lowerBorder or input.empty())
        throw CreationException();
    max = 0;
    for (const auto &elem: input) {
        if (elem > max)
            max = elem;
        if (elem < lowerBorder) {
            Bins[0]++;
            continue;
        }
        if (elem > upperBoarder) {
            auto maximum = max_element(Bins.begin(), Bins.end())->first;
            Bins[maximum]++;
            continue;
        }
        Bins[elem - 1]++;

    }
    binCount = Bins.size();
    min = Bins[0];
}

bool Histogram::operator==(const Histogram &that) const {
    if (Bins.size() != that.Bins.size() or min != that.min or max != that.max or binCount != that.binCount)
        return false;
    for (const auto &elem : that.Bins) {
        auto elemIter = Bins.find(elem.first);
        if (elemIter == Bins.end())
            return false;
        else {
            if (elemIter->second != elem.second)
                return false;
        }
    }
    return true;
}

Histogram Histogram::operator+(const Histogram &that) const {
    if (that == Histogram())
        return *this;
    if (*this == Histogram())
        return that;
    if (this->max != that.max or this->min != that.min or this->binCount != that.binCount)
        throw ArithmeticException();
    Histogram newHist = Histogram(*this);
    for (const auto &elem : that.Bins) {
        newHist.Bins[elem.first] += elem.second;
    }
    return newHist;
}

Histogram Histogram::operator-(const Histogram &that) const {
    if (that == Histogram())
        return *this;
    if (*this == Histogram())
        return that;
    if (this->max != that.max or this->min != that.min or this->binCount != that.binCount)
        throw ArithmeticException();
    Histogram newHist = Histogram(*this);
    for (const auto &elem : that.Bins) {
        newHist.Bins[elem.first] -= elem.second;
        if (newHist.Bins[elem.first] <= 0) {
            newHist.Bins.erase(elem.first);
            newHist.binCount--;
        }
    }
    if (newHist.begin() != newHist.end()) {
        auto newMin = newHist.begin()->second;
        map<int, int>::reverse_iterator newMaxIt;
        newMaxIt = newHist.Bins.rbegin();
        auto newMax = newMaxIt->second;
        newHist.max = newMax;
        newHist.min = newMin;
    } else {
        newHist.min = 0;
        newHist.max = 0;
    }
    return newHist;
}

Histogram::iterator Histogram::begin() {
    return Bins.begin();
}

Histogram::iterator Histogram::end() {
    return Bins.end();
}

//Histogram::const_iterator Histogram::cbegin() {
//    return Bins.cbegin();
//}
//
//Histogram::const_iterator Histogram::cend() {
//    return Bins.cend();
//}

Histogram::Histogram() {
    binCount = 0;
    max = 0;
    min = 0;
    Bins = map<int, int>();
}

Histogram::const_iterator Histogram::cbegin() const {
    return Bins.cbegin();
}

Histogram::const_iterator Histogram::cend() const {
    return Bins.cend();
}
