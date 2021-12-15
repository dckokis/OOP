#include <gtest/gtest.h>
#include "old.h"

unsigned int Hash(int data) {
    int N = 13;
    double A = 0.618033;
    int h = N * fmod(data * A, 1);
    return h;
}

TEST(OldBloom, SimpleTest) {
    auto a = bloom_filter_new(10, reinterpret_cast<BloomFilterHashFunc>(Hash), 5);
    int* val = new int(1);
    bloom_filter_insert(a, val);
    ASSERT_EQ(bloom_filter_query(a, val), 1);
}