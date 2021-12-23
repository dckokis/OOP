#pragma once

#include <vector>
#include <stdexcept>
#include "bloomFilter.hpp"
#include "old.h"


class bloomAdapter final: public  BloomFilterNamespace::BaseFilter<void*>
{
    BloomFilter* bf;
public:
    bloomAdapter(unsigned int tableSize, BloomFilterHashFunc hashFunc, unsigned int numFunc) {
        bf = bloom_filter_new(tableSize, hashFunc, numFunc);
        if (!bf){
            throw BloomFilterNamespace::BloomExceptions("Bad memory allocation for C bloom filter");
        }
    }
    explicit bloomAdapter(BloomFilter* bf_) {
        if (!bf){
            bloom_filter_free(bf);
        }
        bf = bf_;
    }

    ~bloomAdapter() override {
        bloom_filter_free(bf);
    }
    void insert(void* const& value) override {
        bloom_filter_insert(bf, value);
    }
    bool query(void* const& value) override {
        return bloom_filter_query(bf, value);
    }
    void read(std::vector<unsigned char>& array) override {
        bloom_filter_read(bf, array.data());
    }
    void load(std::vector<unsigned char>& array) override {
        bloom_filter_load(bf, array.data());
    }
    BaseFilter<void*>* BloomFiltersUnion(BaseFilter* filter2) override {
        auto bf2 = dynamic_cast<bloomAdapter *>(filter2)->data();
        auto res = bloom_filter_union(bf, bf2);
        if (!res) {
            return new BloomFilterNamespace::NULLbloom<void *>;
        }
        return new bloomAdapter(res);
    }
    BaseFilter<void*>* BloomFiltersIntersection(BaseFilter* filter2) override {
        auto bf2 = dynamic_cast<bloomAdapter *>(filter2)->data();
        auto res = bloom_filter_intersection(bf, bf2);
        if (!res) {
            return new BloomFilterNamespace::NULLbloom<void *>;
        }
        return new bloomAdapter(res);
    }

    BloomFilter* data() {
        return bf;
    }
};