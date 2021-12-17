#include <gtest/gtest.h>
#include "old.h"

unsigned int IntHash(void* data) {
    auto x = static_cast<int *>(data);
    int N = 13;
    double A = 0.618033;
    int h = N * fmod(*x * A, 1);
    return h;
}

unsigned int StringHash(void* data) {
    auto* x = static_cast<std::string *>(data);
    auto len = x->length();
    int N = 17;
    double A = 0.618033;
    int h = N * fmod(len * A, 1);
    return h;
}


TEST(OldBloom, IntTest) {
    auto a = bloom_filter_new(10, IntHash, 5);
    auto val = new int(1);
    auto falseVal = new int(2);
    bloom_filter_insert(a, val);
    ASSERT_EQ(bloom_filter_query(a, val), 1);
    ASSERT_EQ(bloom_filter_query(a, falseVal), 0);
    bloom_filter_free(a);
}

TEST(OldBloom, StringTest) {
    auto a = bloom_filter_new(5, StringHash, 5);
    auto string = "hello";
    auto falseData = "helloooworld";
    bloom_filter_insert(a, &string);
    ASSERT_EQ(bloom_filter_query(a, &string), 1);
    ASSERT_EQ(bloom_filter_query(a, &falseData), 0);
    bloom_filter_free(a);
}

TEST(OldBloom, Union) {
    auto first = bloom_filter_new(5, IntHash, 5);
    auto second = bloom_filter_new(5, IntHash, 5);
    auto firstVal = new int(1);
    auto secondVal = new int(2);
    bloom_filter_insert(first, firstVal);
    bloom_filter_insert(second, secondVal);
    ASSERT_EQ(bloom_filter_query(first, firstVal), 1);
    ASSERT_EQ(bloom_filter_query(second, secondVal), 1);
    auto united = bloom_filter_union(first, second);
    ASSERT_EQ(bloom_filter_query(united, firstVal), 1);
    ASSERT_EQ(bloom_filter_query(united, secondVal), 1);
}

TEST(OldBloom, Intersection){
    auto first = bloom_filter_new(5, IntHash, 5);
    auto second = bloom_filter_new(5, IntHash, 5);
    auto firstVal = new int(1);
    auto secondVal = new int(2);
    auto thirdVal = new int(3);
    bloom_filter_insert(first, firstVal);
    bloom_filter_insert(second, secondVal);
    bloom_filter_insert(first, thirdVal);
    bloom_filter_insert(second, thirdVal);
    ASSERT_EQ(bloom_filter_query(first, firstVal), 1);
    ASSERT_EQ(bloom_filter_query(second, secondVal), 1);
    ASSERT_EQ(bloom_filter_query(first, thirdVal), 1);
    ASSERT_EQ(bloom_filter_query(second, thirdVal), 1);
    auto intersection = bloom_filter_intersection(first, second);
    ASSERT_EQ(bloom_filter_query(intersection, thirdVal), 1);
}

TEST(OldBloom, read) {
    auto first = bloom_filter_new(5, IntHash, 5);
    auto firstVal = new int(1);
    auto secondVal = new int(2);
    bloom_filter_insert(first, firstVal);
    bloom_filter_insert(first, secondVal);
    auto *array = new unsigned char();
    bloom_filter_read(first, array);
}