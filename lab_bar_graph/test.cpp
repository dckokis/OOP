#include "gtest/gtest.h"
#include "Histogram.hpp"
#include "histogramExceptions.hpp"

using namespace std;

TEST(Constructor, EmptyVector) {
    vector<int> empty;
    ASSERT_THROW(Histogram(empty, 1, 10), CreationException);
}

TEST(Constructor, IncorrectMinMax) {
    vector<int> input{1, 2, 3, 3, 4, 5};
    ASSERT_THROW(Histogram(input, -1, 0), CreationException);
    ASSERT_THROW(Histogram(input, 4, 5), CreationException);
}

TEST(Constructor, CorrectData) {
    map<int, int> test{{0, 1},
                       {1, 1},
                       {2, 2}};
    vector<int> input{1, 2, 3, 3};
    auto testHist = Histogram(input, 4, 0);
    ASSERT_TRUE(test.begin()->first == testHist.begin()->first);
    ASSERT_TRUE(test.begin()->second == testHist.begin()->second);
}

TEST(Operators, Addition) {
    map<int, int> test{{0, 2},
                       {1, 3},
                       {2, 3}};
    vector<int> input1{1, 2, 3, 3};
    vector<int> input2{1, 2, 2, 3};
    vector<int> input3{1, 1, 1, 1, 1};
    auto testHist1 = Histogram(input1, 4, 0);
    auto testHist2 = Histogram(input2, 4, 0);
    auto testHist3 = Histogram(input3, 4, 1);
    ASSERT_TRUE(test.begin()->first == (testHist1 + testHist2).begin()->first);
    ASSERT_THROW(testHist1 + testHist3, ArithmeticException);

    auto emptyHist = Histogram();
    ASSERT_TRUE(testHist1 + emptyHist == testHist1);
    ASSERT_TRUE(emptyHist + testHist1 == testHist1);
}

TEST(Operators, Substraction) {
    map<int, int> test{{1, 1},};
    vector<int> input1{1, 2, 3, 3};
    vector<int> input2{1, 2, 2, 3};
    vector<int> input3{1, 1, 1, 1, 1};
    auto testHist1 = Histogram(input1, 4, 0);
    auto testHist2 = Histogram(input2, 4, 0);
    auto testHist3 = Histogram(input3, 4, 1);
    auto emptyHist = Histogram();
    ASSERT_TRUE(test.begin()->first == (testHist2 - testHist1).begin()->first);
    ASSERT_THROW(testHist1 - testHist3, ArithmeticException);
    ASSERT_TRUE(testHist1 - testHist1 == emptyHist);
    ASSERT_TRUE(testHist1 - emptyHist == testHist1);
}

TEST(Operators, Equality) {
    vector<int> input1{1, 2, 3, 3};
    vector<int> input2{1, 2, 3, 3};
    vector<int> input3{1, 1, 1, 1, 1};
    auto testHist1 = Histogram(input1, 4, 0);
    auto testHist2 = Histogram(input2, 4, 0);
    auto testHist3 = Histogram(input3, 4, 1);
    ASSERT_TRUE(testHist1 == testHist2);
    ASSERT_FALSE(testHist3 == testHist1);
}

