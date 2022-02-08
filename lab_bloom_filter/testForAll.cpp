#include "Adapter.hpp" // for C code tests lines 21-23 must be uncommented, comment lines 24-26
#include <gtest/gtest.h>
#include "bloomFilter.hpp"

using namespace BloomFilterNamespace;
using namespace std;

unsigned int HashFunction(void *data) {
    return hash<void *>()(data);
}

class BloomFilterTest : public testing::Test {
protected:
    BaseFilter<void *> *bloomFirst;
    BaseFilter<void *> *bloomSecond;
    BaseFilter<void *> *bloomThird;
    BaseFilter<void *> *bloomFourth;
    BaseFilter<void *> *bloomFifth;

    void SetUp() override {
//        bloomFirst = new bloomAdapter(4, HashFunction, 4);
//        bloomSecond = new bloomAdapter(4, HashFunction, 4);
//        bloomThird = new bloomAdapter(15, HashFunction, 6);
        bloomFirst = new bloomFilter<void *>(4, 4);
        bloomSecond = new bloomFilter<void *>(4, 4);
        bloomThird = new bloomFilter<void *>(15, 6);
    }

    void TearDown() override {
        delete bloomFirst;
        delete bloomSecond;
        delete bloomThird;
    }
};

TEST_F(BloomFilterTest, BloomLoadRead) {
    {
        vector<unsigned char> loadFirst{5};
        vector<unsigned char> loadSecond(1);
        vector<unsigned char> readSecond(1);
        bloomFirst->load(loadFirst);
        bloomSecond->load(loadFirst);
        bloomFirst->read(loadSecond);
        bloomSecond->read(readSecond);
        EXPECT_EQ(loadFirst[0], loadSecond[0]);
        EXPECT_EQ(loadSecond[0], readSecond[0]);
    }
    {
        vector<unsigned char> arr{5, 6};
        vector<unsigned char> arr1(2);
        bloomThird->load(arr);
        bloomThird->read(arr1);
        EXPECT_EQ(arr[0], arr1[0]);
        EXPECT_EQ(arr[1], arr1[1]);
    }
    {
        vector<unsigned char> arr{5};
        vector<unsigned char> arr1(1);
        bloomFourth = bloomFirst->BloomFiltersIntersection(bloomThird);
        bloomFourth->load(arr);
        bloomFourth->read(arr1);
        EXPECT_FALSE(arr[0] == arr1[0]);
        delete bloomFourth;
    }
}


TEST_F(BloomFilterTest, BloomInsertQuery) {
    int a = 5;
    bloomFirst->insert(&a);
    EXPECT_TRUE(bloomFirst->query(&a));
}

TEST_F(BloomFilterTest, BloomIntersection) {
    /*with 1 value*/
    {
        int a = 5;
        bloomFirst->insert(&a);
        bloomSecond->insert(&a);
        bloomFourth = bloomSecond->BloomFiltersIntersection(bloomFirst);
        EXPECT_TRUE(bloomFourth->query(&a));
        delete bloomFourth;
    }
    /*with 2 values*/
    {
        int a = 5;
        int b = 6;
        bloomFirst->insert(&a);
        bloomFirst->insert(&b);
        bloomSecond->insert(&a);
        bloomSecond->insert(&b);
        bloomFourth = bloomSecond->BloomFiltersIntersection(bloomFirst);
        EXPECT_TRUE(bloomFourth->query(&a));
        EXPECT_TRUE(bloomFourth->query(&b));
        delete bloomFourth;
    }
    /*with null*/
    {
        int a = 5;
        bloomFirst->insert(&a);
        bloomThird->insert(&a);
        bloomFourth = bloomThird->BloomFiltersIntersection(bloomFirst);
        bloomFifth = bloomFourth->BloomFiltersIntersection(bloomFirst);
        EXPECT_FALSE(bloomFourth->query(&a));
        EXPECT_FALSE(bloomFifth->query(&a));
        delete bloomFourth;
        delete bloomFifth;
    }
    /*with itself*/
    {
        int a = 5;
        bloomFirst->insert(&a);
        bloomFourth = bloomFirst->BloomFiltersIntersection(bloomFirst);
        EXPECT_TRUE(bloomFourth->query(&a));
        delete bloomFourth;
    }
    /*itself 2 values*/
    {
        int a = 5;
        int b = 6;
        bloomFirst->insert(&a);
        bloomFirst->insert(&b);
        bloomFourth = bloomFirst->BloomFiltersIntersection(bloomFirst);
        EXPECT_TRUE(bloomFourth->query(&a));
        EXPECT_TRUE(bloomFourth->query(&b));
        delete bloomFourth;
    }
    /*with null*/
    {
        int a = 5;
        bloomFirst->insert(&a);
        bloomThird->insert(&a);
        bloomFourth = bloomThird->BloomFiltersIntersection(bloomFirst);
        EXPECT_FALSE(bloomFourth->query(&a));
        delete bloomFourth;
    }
    /*with null 2 values*/
    {
        int a = 5;
        bloomFirst->insert(&a);
        bloomSecond->insert(&a);
        bloomThird->insert(&a);
        bloomFourth = bloomSecond->BloomFiltersIntersection(bloomFirst);
        bloomFifth = bloomThird->BloomFiltersIntersection(bloomFourth);
        EXPECT_TRUE(bloomFourth->query(&a));
        EXPECT_FALSE(bloomFifth->query(&a));
        delete bloomFourth;
        delete bloomFifth;
    }
}


TEST_F(BloomFilterTest, bfUnion) {
    /*with 2 values*/
    {
        int a = 5;
        int b = 6;
        bloomFirst->insert(&a);
        bloomSecond->insert(&b);
        bloomFourth = bloomSecond->BloomFiltersUnion(bloomFirst);
        EXPECT_TRUE(bloomFourth->query(&a));
        EXPECT_TRUE(bloomFourth->query(&b));
        delete bloomFourth;
    }
    /*with 3 values*/
    {
        int a = 5;
        int b = 6;
        int c = 7;
        bloomFirst->insert(&a);
        bloomFirst->insert(&c);
        bloomSecond->insert(&b);
        bloomFourth = bloomSecond->BloomFiltersUnion(bloomFirst);
        EXPECT_TRUE(bloomFourth->query(&a));
        EXPECT_TRUE(bloomFourth->query(&b));
        EXPECT_TRUE(bloomFourth->query(&c));
        delete bloomFourth;
    }
    /*with null*/
    {
        int a = 5;
        int b = 6;
        bloomFirst->insert(&a);
        bloomThird->insert(&b);
        bloomFourth = bloomThird->BloomFiltersUnion(bloomFirst);
        bloomFifth = bloomFourth->BloomFiltersUnion(bloomFirst);
        EXPECT_FALSE(bloomFourth->query(&a));
        EXPECT_FALSE(bloomFifth->query(&a));
        EXPECT_FALSE(bloomFourth->query(&b));
        EXPECT_FALSE(bloomFifth->query(&b));
        delete bloomFourth;
        delete bloomFifth;
    }
    /*union with united*/
    {
        int a = 5;
        int b = 6;
        bloomFirst->insert(&a);
        bloomSecond->insert(&b);
        bloomThird->insert(&b);
        bloomFourth = bloomSecond->BloomFiltersUnion(bloomFirst);
        bloomFifth = bloomThird->BloomFiltersUnion(bloomFourth);
        EXPECT_TRUE(bloomFourth->query(&a));
        EXPECT_TRUE(bloomFourth->query(&b));
        EXPECT_FALSE(bloomFifth->query(&b));
        EXPECT_FALSE(bloomFifth->query(&a));
        delete bloomFourth;
        delete bloomFifth;
    }
}