#include "gtest/gtest.h"
#include "FilterIterator.hpp"

using namespace std;
using namespace FilterIterator;

struct is_even {
    bool operator()(int x) { return x % 2 == 0; }
};

struct is_four {
    bool operator()(int x) { return x == 4; }
};

TEST(FilterIterator, VectorInt) {
    is_even pred;
    auto v = std::vector{1, 2, 3, 4};
    auto f = makeFilterIterator<is_even, vector<int>::iterator>(pred, v.begin(), v.end());
    ASSERT_TRUE(*f == 2);
    ++f;
    ASSERT_TRUE(*f == 4);
}

TEST(FilterIterator, VectorDouble) {
    struct is_suitable {
        bool operator()(double x) {
            for (int i = 0; i < 10; i++) {
                if (x / 1.1 == i) return true;
            }
            return false;
        }
    };
    is_suitable pred;
    auto v = std::vector{1.0, 2.2, 3.1, 4.4};
    auto f = makeFilterIterator<is_suitable, vector<double>::iterator>(pred, v.begin(), v.end());
    ASSERT_TRUE(*f == 2.2);
    ++f;
    ASSERT_TRUE(*f == 4.4);
}


TEST(FilterIterator, NoSuitableElems) {
    is_even pred;
    auto v = std::vector{1, 3, 5, 7};
    auto f = makeFilterIterator<is_even, vector<int>::iterator>(pred, v.begin(), v.end());
    ASSERT_THROW(*f, OutOfRangeException);
}

TEST(FilterIterator, FilterFromFilter) {
    auto v = std::vector{1, 2, 3, 4};
    is_even isEven;
    is_four isFour;
    auto f = makeFilterIterator<is_even, vector<int>::iterator>(isEven, v.begin(), v.end());
    auto anEnd = f;
    ++anEnd;
    ++anEnd;
    auto ff = makeFilterIterator<is_four, decltype(f)>(isFour, f, anEnd);
    ASSERT_TRUE(*(++f) == *ff);
}

