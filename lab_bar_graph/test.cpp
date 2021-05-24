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
    ASSERT_TRUE(test[0] == testHist.getBins()[0]);
    ASSERT_TRUE(test[1] == testHist.getBins()[1]);
    ASSERT_TRUE(test[2] == testHist.getBins()[2]);
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
    ASSERT_TRUE(test == (testHist1 + testHist2).getBins());
    ASSERT_THROW(testHist1 + testHist3, ArithmeticException);
}

TEST(Operators, Substraction) {
    map<int, int> test{{0, 0},
                       {1, 1},};
    vector<int> input1{1, 2, 3, 3};
    vector<int> input2{1, 2, 2, 3};
    vector<int> input3{1, 1, 1, 1, 1};
    auto testHist1 = Histogram(input1, 4, 0);
    auto testHist2 = Histogram(input2, 4, 0);
    auto testHist3 = Histogram(input3, 4, 1);
    ASSERT_TRUE(test == (testHist2 - testHist1).getBins());
    ASSERT_THROW(testHist1 - testHist3, ArithmeticException);
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