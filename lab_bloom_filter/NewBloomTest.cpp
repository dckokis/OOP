#include "bloomFilter.hpp"
#include <gtest/gtest.h>

using namespace Bloom;
using namespace std;
size_t IntHash(const int &data) {
    int N = 13;
    double A = 0.618033;
    int h = N * fmod(data * A, 1);
    return h;
}

unsigned int StringHash(const string& data) {
    auto len = data.length();
    int N = 17;
    double A = 0.618033;
    int h = N * fmod(len * A, 1);
    return h;
}

TEST(Bloom, FalseConstructor) {
    ASSERT_THROW(new BloomFilter<int>(0, nullptr, 10), BloomExceptions);
    ASSERT_THROW(new BloomFilter<int>(0, IntHash, 100), BloomExceptions);
}

TEST(Bloom, insert) {
    /*int*/
    {
        BloomFilter<int> test(5, IntHash, 5);
        int data = 1;
        test.insert(data);
        ASSERT_TRUE(test.query(data));
        int y;
        auto &emptyData = y;
        test.insert(emptyData);
        ASSERT_TRUE(test.query(emptyData));
    }
    /*string*/
    {
        BloomFilter<string> test(5, StringHash, 5);
        auto data = "hello";
        test.insert(data);
        ASSERT_TRUE(test.query(data));
        auto emptyData = string();
        test.insert(emptyData);
        ASSERT_TRUE(test.query(emptyData));
    }
}

TEST(Bloom, query) {
    /*int*/
    {
        BloomFilter<int> test(5, IntHash, 5);
        int data = 1;
        test.insert(data);
        int falseData = 2;
        ASSERT_TRUE(test.query(data));
        ASSERT_FALSE(test.query(falseData));
    }
    /*string*/
    {
        BloomFilter<string> test(5, StringHash, 5);
        auto data = "hello";
        test.insert(data);
        auto falseData = "world";
        auto falseData1 = "helloooworld";
        ASSERT_TRUE(test.query(data));
        ASSERT_FALSE(test.query(falseData1));
        //ASSERT_FALSE(test.query(falseData)); such code will cause false positive match
    }
}

TEST(Bloom, read) {
    BloomFilter<int> test(5, IntHash, 5);
    int data1 = 1;
    test.insert(data1);
    int data2 = 2;
    test.insert(data2);
    ASSERT_TRUE(test.query(data1));
    ASSERT_TRUE(test.query(data2));
    auto copy = vector<unsigned char>();
    test.read(copy);
    ASSERT_EQ(copy.size(), 5);
}

TEST(Bloom, Union) {
    BloomFilter<int> first(5, IntHash, 5);
    int data = 1;
    first.insert(data);
    ASSERT_TRUE(first.query(data));
    BloomFilter<int> second(5, IntHash, 5);
    int anotherData = 2;
    second.insert(anotherData);
    ASSERT_TRUE(second.query(anotherData));
    auto united = BloomFilter<int>::BloomFiltersUnion(first, second);
    ASSERT_TRUE(united.query(data));
    ASSERT_TRUE(united.query(anotherData));
    BloomFilter<int> third(10, IntHash, 5);
    ASSERT_THROW(BloomFilter<int>::BloomFiltersUnion(third, second), BloomExceptions);
}

TEST(Bloom, Intersection) {
    BloomFilter<int> first(10, IntHash, 5);
    int data1 = 1;
    int data2 = 99;
    first.insert(data1);
    first.insert(data2);
    ASSERT_TRUE(first.query(data1));
    ASSERT_TRUE(first.query(data2));
    BloomFilter<int> second(10, IntHash, 5);
    int anotherData1 = 1;
    int anotherData2 = 3;
    second.insert(anotherData1);
    second.insert(anotherData2);
    ASSERT_TRUE(second.query(anotherData1));
    ASSERT_TRUE(second.query(anotherData2));
    auto intersection = BloomFilter<int>::BloomFiltersIntersection(first, second);
    ASSERT_TRUE(intersection.query(data1));
    ASSERT_TRUE(intersection.query(anotherData1));
    ASSERT_FALSE(intersection.query(data2));
    ASSERT_FALSE(intersection.query(anotherData2));
}