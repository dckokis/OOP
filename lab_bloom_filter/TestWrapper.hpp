#pragma once

#include <vector>
#include <stdexcept>
#include "bloomFilter.hpp"
#include "old.h"


class BloomFilterAdapter final: public  Bloom::baseFilter<void*>
{
    BloomFilter* bf;
public:
    BloomFilterAdapter(unsigned int tableSize, BloomFilterHashFunc hashFunc, unsigned int numFunc);
    explicit BloomFilterAdapter(BloomFilter* bf);

    ~BloomFilterAdapter() override;
    void insert(void* const& value) override;
    bool query(void* const& value) override;
    void read(std::vector<unsigned char>& array) override;
    void load(std::vector<unsigned char>& array) override;
    baseFilter<void*>* BloomFiltersUnion(baseFilter* filter2) override;
    baseFilter<void*>* BloomFiltersIntersection(baseFilter* filter2) override;

    BloomFilter* data();
};