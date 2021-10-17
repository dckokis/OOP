#include "gtest/gtest.h"
#include "FilterIterator.hpp"

using namespace std;
using namespace filteriter;

struct is_even {
    bool operator()(int x) { return x % 2 == 0; }
};

struct is_four {
    bool operator()(int x) { return x == 4; }
};

class IsEqualToMyNumber final {
private:
    int m_num = 20052;
public:
    bool operator()(int x) { return x == m_num; }
};

TEST(filteriter, VectorInt) {
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
    ASSERT_THROW(*f, FilterIteratorExceptions);
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

//TEST(FilterIterator, OtherIterator) {
//    auto v = std::vector{1, 2, 3, 4};
//    is_even isEven;
//    auto f1 = makeFilterIterator<is_even, vector<int>::iterator>(isEven, v.begin(), v.end());
//    auto f2 = FilterIterator(f1);
//}

TEST(FilterIterator, PredicateClass) {
    ASSERT_TRUE(is_default_constructible_v<IsEqualToMyNumber>);
    auto v = vector<int>{1, 3, 20052, 33, 0, 20052};
    auto f = makeFilterIterator<IsEqualToMyNumber>(v.begin(), v.end());
    ASSERT_EQ(*f, 20052);
    f++;
    ASSERT_EQ(*f, 20052);
}

TEST(Operators, Equality) {
    is_even pred;
    auto v = std::vector{1, 2, 3, 4};
    auto f1 = makeFilterIterator<is_even, vector<int>::iterator>(pred, v.begin(), v.end());
    auto f2 = makeFilterIterator<is_even, vector<int>::iterator>(pred, v.begin(), v.end());
    ASSERT_TRUE(f1 == f2);
    f1++;
    f2++;
    ASSERT_TRUE(f1 == f2);
}

TEST(Operators, NotEquality) {
    is_even pred;
    auto v = std::vector{1, 2, 3, 4};
    auto f1 = makeFilterIterator<is_even, vector<int>::iterator>(pred, v.begin(), v.end());
    auto f2 = makeFilterIterator<is_even, vector<int>::iterator>(pred, v.begin(), v.end());
    f1++;
    ASSERT_TRUE(f1 != f2);
}

TEST(Operators, Dereference) {
    is_even pred;
    auto v = std::vector{1, 2, 3, 4};
    auto f1 = makeFilterIterator<is_even, vector<int>::iterator>(pred, v.begin(), v.end());
    ASSERT_EQ(2, *f1);
    ++f1;
    ASSERT_EQ(4, *f1);
    f1++;
    ASSERT_THROW(*f1, FilterIteratorExceptions);
}

TEST(Operators, Prefix) {
    is_even pred;
    auto v = std::vector{1, 2, 3, 4};
    auto f1 = makeFilterIterator<is_even, vector<int>::iterator>(pred, v.begin(), v.end());
    ASSERT_EQ(4, *(++f1));
}

TEST(Operators, Postfix) {
    is_even pred;
    auto v = std::vector{1, 2, 3, 4};
    auto f1 = makeFilterIterator<is_even, vector<int>::iterator>(pred, v.begin(), v.end());
    ASSERT_EQ(2, *(f1++));
}

TEST(Methods, base) {
    is_even pred;
    auto v = std::vector{1, 2, 3, 4};
    auto f1 = makeFilterIterator<is_even, vector<int>::iterator>(pred, v.begin(), v.end());
    auto begin = v.begin();
    ASSERT_EQ(f1.base(), ++begin);
}

TEST(Methods, end) {
    is_even pred;
    auto v = std::vector{1, 2, 3, 4};
    auto f1 = makeFilterIterator<is_even, vector<int>::iterator>(pred, v.begin(), v.end());
    auto end = v.end();
    ASSERT_EQ(f1.end(), end);
}


