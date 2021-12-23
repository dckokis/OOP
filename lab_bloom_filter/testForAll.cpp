#include "Adapter.hpp"
#include <gtest/gtest.h>
#include "bloomFilter.hpp"

using namespace BloomFilterNamespace;
using namespace std;

unsigned int hashf(void *data) {
    return std::hash<void *>()(data);
}

class BloomFilterTest : public testing::Test {
protected:
    BaseFilter<void *> *bloomFirst;
    BaseFilter<void *> *bloomSecond;
    BaseFilter<void *> *bloomThird;
    BaseFilter<void *> *bloomFourth;
    BaseFilter<void *> *bloomFifth;

    void SetUp() override {
//        bloomFirst = new bloomAdapter(4, hashf, 4);
//        bloomSecond = new bloomAdapter(4, hashf, 4);
//        bloomThird = new bloomAdapter(15, hashf, 6);
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

TEST_F(BloomFilterTest, bfLoadRead) {
    std::vector<unsigned char> arr{5};
    std::vector<unsigned char> arr1(1);
    std::vector<unsigned char> arr2(1);
    bloomFirst->load(arr);
    bloomSecond->load(arr);
    bloomFirst->read(arr1);
    bloomSecond->read(arr2);
    EXPECT_EQ(arr[0], arr1[0]);
    EXPECT_EQ(arr1[0], arr2[0]);
}

TEST_F(BloomFilterTest, bfLoadReadNull) {
    std::vector<unsigned char> arr{5};
    std::vector<unsigned char> arr1(1);
    bloomFourth = bloomFirst->BloomFiltersIntersection(bloomThird);
    bloomFourth->load(arr);
    bloomFourth->read(arr1);
    EXPECT_FALSE(arr[0] == arr1[0]);
    delete bloomFourth;
}

TEST_F(BloomFilterTest, bfLoadRead16) {
    std::vector<unsigned char> arr{5, 6};
    std::vector<unsigned char> arr1(2);
    bloomThird->load(arr);
    bloomThird->read(arr1);
    EXPECT_EQ(arr[0], arr1[0]);
    EXPECT_EQ(arr[1], arr1[1]);
}

TEST_F(BloomFilterTest, bfInsertQuery) {
    int a = 5;
    bloomFirst->insert(&a);
    EXPECT_EQ(bloomFirst->query(&a), 1);
}

TEST_F(BloomFilterTest, bfIntersection) {
    int a = 5;
    bloomFirst->insert(&a);
    bloomSecond->insert(&a);
    bloomFourth = bloomSecond->BloomFiltersIntersection(bloomFirst);
    EXPECT_EQ(bloomFourth->query(&a), 1);
    delete bloomFourth;
}

TEST_F(BloomFilterTest, bfIntersectionWithNull) {
    int a = 5;
    bloomFirst->insert(&a);
    bloomThird->insert(&a);
    bloomFourth = bloomThird->BloomFiltersIntersection(bloomFirst);
    bloomFifth = bloomFourth->BloomFiltersIntersection(bloomFirst);
    EXPECT_EQ(bloomFourth->query(&a), 0);
    EXPECT_EQ(bloomFifth->query(&a), 0);
    delete bloomFourth;
    delete bloomFifth;
}


TEST_F(BloomFilterTest, bfIntersectionItself) {
    int a = 5;
    bloomFirst->insert(&a);
    bloomFourth = bloomFirst->BloomFiltersIntersection(bloomFirst);
    EXPECT_EQ(bloomFourth->query(&a), 1);
    delete bloomFourth;
}

TEST_F(BloomFilterTest, bfIntersectionItself2) {
    int a = 5;
    int b = 6;
    bloomFirst->insert(&a);
    bloomFirst->insert(&b);
    bloomFourth = bloomFirst->BloomFiltersIntersection(bloomFirst);
    EXPECT_EQ(bloomFourth->query(&a), 1);
    EXPECT_EQ(bloomFourth->query(&b), 1);
    delete bloomFourth;
}

TEST_F(BloomFilterTest, bfIntersection2) {
    int a = 5;
    int b = 6;
    bloomFirst->insert(&a);
    bloomFirst->insert(&b);
    bloomSecond->insert(&a);
    bloomSecond->insert(&b);
    bloomFourth = bloomSecond->BloomFiltersIntersection(bloomFirst);
    EXPECT_EQ(bloomFourth->query(&a), 1);
    EXPECT_EQ(bloomFourth->query(&b), 1);
    delete bloomFourth;
}

TEST_F(BloomFilterTest, bfNULLIntersection) {
    int a = 5;
    bloomFirst->insert(&a);
    bloomThird->insert(&a);
    bloomFourth = bloomThird->BloomFiltersIntersection(bloomFirst);
    EXPECT_EQ(bloomFourth->query(&a), 0);
    delete bloomFourth;
}

TEST_F(BloomFilterTest, bfNULLIntersection2) {
    int a = 5;
    bloomFirst->insert(&a);
    bloomSecond->insert(&a);
    bloomThird->insert(&a);
    bloomFourth = bloomSecond->BloomFiltersIntersection(bloomFirst);
    bloomFifth = bloomThird->BloomFiltersIntersection(bloomFourth);
    EXPECT_EQ(bloomFourth->query(&a), 1);
    EXPECT_EQ(bloomFifth->query(&a), 0);
    delete bloomFourth;
    delete bloomFifth;
}

TEST_F(BloomFilterTest, bfUnion) {
    int a = 5;
    int b = 6;
    bloomFirst->insert(&a);
    bloomSecond->insert(&b);
    bloomFourth = bloomSecond->BloomFiltersUnion(bloomFirst);
    EXPECT_EQ(bloomFourth->query(&a), 1);
    EXPECT_EQ(bloomFourth->query(&b), 1);
    delete bloomFourth;
}

TEST_F(BloomFilterTest, bfUnionWithNull) {
    int a = 5;
    int b = 6;
    bloomFirst->insert(&a);
    bloomThird->insert(&b);
    bloomFourth = bloomThird->BloomFiltersUnion(bloomFirst);
    bloomFifth = bloomFourth->BloomFiltersUnion(bloomFirst);
    EXPECT_EQ(bloomFourth->query(&a), 0);
    EXPECT_EQ(bloomFifth->query(&a), 0);
    EXPECT_EQ(bloomFourth->query(&b), 0);
    EXPECT_EQ(bloomFifth->query(&b), 0);
    delete bloomFourth;
    delete bloomFifth;
}

TEST_F(BloomFilterTest, bfUnion3) {
    int a = 5;
    int b = 6;
    int c = 7;
    bloomFirst->insert(&a);
    bloomFirst->insert(&c);
    bloomSecond->insert(&b);
    bloomFourth = bloomSecond->BloomFiltersUnion(bloomFirst);
    EXPECT_EQ(bloomFourth->query(&a), 1);
    EXPECT_EQ(bloomFourth->query(&b), 1);
    EXPECT_EQ(bloomFourth->query(&c), 1);
    delete bloomFourth;
}

TEST_F(BloomFilterTest, bfNULLUnion) {
    int a = 5;
    int b = 6;
    bloomFirst->insert(&a);
    bloomThird->insert(&b);
    bloomFourth = bloomThird->BloomFiltersUnion(bloomFirst);
    EXPECT_EQ(bloomFourth->query(&a), 0);
    EXPECT_EQ(bloomFourth->query(&b), 0);
    delete bloomFourth;
}


TEST_F(BloomFilterTest, bfNULLUnion2) {
    int a = 5;
    int b = 6;
    bloomFirst->insert(&a);
    bloomSecond->insert(&b);
    bloomThird->insert(&b);
    bloomFourth = bloomSecond->BloomFiltersUnion(bloomFirst);
    bloomFifth = bloomThird->BloomFiltersUnion(bloomFourth);
    EXPECT_EQ(bloomFourth->query(&a), 1);
    EXPECT_EQ(bloomFourth->query(&b), 1);
    EXPECT_EQ(bloomFifth->query(&b), 0);
    EXPECT_EQ(bloomFifth->query(&a), 0);
    delete bloomFourth;
    delete bloomFifth;
}