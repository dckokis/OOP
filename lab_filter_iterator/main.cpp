#include <iostream>
#include <vector>
#include <cassert>
#include "FilterIterator.hpp"


using namespace std;
using namespace filteriterator;

struct is_even {
    bool operator()(int x) { return x % 2 == 0; }
};

struct is_four {
    bool operator()(int x) { return x == 4; }
};

int main() {
//        auto v = std::vector{1, 2, 3, 4};
//        auto i = v.begin();
//        is_even pred;
//        is_four pred4;
//        auto f = makeFilterIterator<is_even, vector<int>::iterator>(pred, i, v.end());
//
////        assert(*f == 2);
////        ++f;
////        assert(*f == 4);
//        auto g = f;
//        ++g;
//        ++g;
//        auto ff = makeFilterIterator<is_four, decltype(f)>(pred4, f, g);
//        auto a = *ff;
//        assert(a == 4);
    is_even pred;
    auto v = std::vector{1, 3, 5, 7};
    auto f = makeFilterIterator<is_even, vector<int>::iterator>(pred, v.begin(), v.end());
    *f;
}
