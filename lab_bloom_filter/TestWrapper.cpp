#include "TestWrapper.hpp"

BloomFilterAdapter::BloomFilterAdapter(unsigned tableSize, BloomFilterHashFunc hashFunc, unsigned numFunc) {
    bf = bloom_filter_new(tableSize, hashFunc, numFunc);
    if (!bf)
        throw Bloom::BloomExceptions("Bad memory allocation for C bloom filter");
}

BloomFilterAdapter::BloomFilterAdapter(BloomFilter *bf_) {
    if (bf)
        bloom_filter_free(bf);
    bf = bf_;
}


BloomFilterAdapter::~BloomFilterAdapter() {
    bloom_filter_free(bf);
}

void BloomFilterAdapter::insert(void *const &value) {
    bloom_filter_insert(bf, value);
}


BloomFilter *BloomFilterAdapter::data() {
    return bf;
}

void BloomFilterAdapter::load(std::vector<unsigned char> &array) {
    bloom_filter_load(bf, array.data());
}

bool BloomFilterAdapter::query(void *const &value) {
    return bloom_filter_query(bf, value);
}

void BloomFilterAdapter::read(std::vector<unsigned char> &array) {
    bloom_filter_read(bf, array.data());
}


Bloom::baseFilter<void *> *BloomFilterAdapter::BloomFiltersIntersection(baseFilter *filter2) {
    auto bf2 = dynamic_cast<BloomFilterAdapter *>(filter2)->data();
    auto res = bloom_filter_intersection(bf, bf2);
    if (!res) {
        return new Bloom::nullFilter<void *>;
    }
    return new BloomFilterAdapter(res);
}

Bloom::baseFilter<void *> *BloomFilterAdapter::BloomFiltersUnion(baseFilter *filter2) {
    auto bf2 = dynamic_cast<BloomFilterAdapter *>(filter2)->data();
    auto res = bloom_filter_union(bf, bf2);
    if (!res) {
        return new Bloom::nullFilter<void *>;
    }
    return new BloomFilterAdapter(res);
}
