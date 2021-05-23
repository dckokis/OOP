#include "Histogram.hpp"
#include <algorithm>

using namespace std;

Histogram::Histogram(std::vector<int> &input, int upperBoarder, int lowerBorder) {
    for (const auto &elem: input) {
        if (elem < lowerBorder)
            Bins[0]++;
        if (elem > upperBoarder) {
            auto maximum = max_element(Bins.begin(), Bins.end())->first;
            Bins[maximum]++;
        }
    }
    binCount = Bins.size();
    max = max_element(Bins.begin(), Bins.end())->second;
    min = Bins[0];
}

bool Histogram::operator==(const Histogram &that) const {
    if (Bins.size() != that.Bins.size())
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
    Histogram newHist = Histogram(*this);
    for (const auto &elem : that.Bins) {
        newHist.Bins[elem.first] += elem.second;
    }
    return newHist;
}

Histogram Histogram::operator-(const Histogram &that) const {
    Histogram newHist = Histogram(*this);
    for (const auto &elem : that.Bins) {
        newHist.Bins[elem.first] -= elem.second;
        if (newHist.Bins[elem.first] < 0)
            newHist.Bins.erase(elem.first);
    }
    return newHist;
}

Histogram::iterator Histogram::begin() {
    return Bins.begin();
}

Histogram::iterator Histogram::end() {
    return Bins.end();
}

std::map<int, int>::const_iterator Histogram::cbegin() const {
    return Bins.cbegin();
}

std::map<int, int>::const_iterator Histogram::cend() const {
    return Bins.cend();
}