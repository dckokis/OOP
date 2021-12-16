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
    std::string* x = static_cast<std::string *>(data);
    auto len = x->length();
    int N = 17;
    double A = 0.618033;
    int h = N * fmod(len * A, 1);
    return h;
}


TEST(OldBloom, IntTest) {
    auto a = bloom_filter_new(10, IntHash, 5);
    int* val = new int(1);
    int* falseVal = new int(2);
    bloom_filter_insert(a, val);
    ASSERT_EQ(bloom_filter_query(a, val), 1);
    ASSERT_EQ(bloom_filter_query(a, falseVal), 0);
    bloom_filter_free(a);
}

TEST(OldBloom, StringTest) {
    auto a = bloom_filter_new(10, StringHash, 5);
    std::string string = "hello";
    bloom_filter_insert(a, &string);
    ASSERT_EQ(bloom_filter_query(a, &string), 1);
    bloom_filter_free(a);
}