#pragma once

#include <vector>
#include <array>

template<typename Value>
class BloomFilter final {
    using HashFunc = size_t (*)(Value data);
public:
    BloomFilter() = delete;

    BloomFilter(size_t size_, HashFunc hashFunc, size_t numFunctions_) : size(size_), hash(hashFunc) {
        if (numFunctions_ < salts.size()) {
            table = std::vector<char>{};
            hash = hashFunc;
            numFunctions = numFunctions_;
        }
    }

    ~BloomFilter() = default;

    void insert(const Value &value) {
        /* Generate hash of the value to insert */
        auto hashValue = hash(value);
        /* Generate multiple unique hashes by XORing with values in the
         * salt table. */
        for (auto i = 0; i < numFunctions; ++i) {
            auto uniqueHash = hashValue ^ salts[i];
            auto index = (uniqueHash % size);
            /* Insert into the table.
             * index / 8 finds the byte index of the table,
             * index % 8 gives the bit index within that byte to set. */
            table[index / 8] |= (1 << (index % 8));
        }
    }

    bool query(const Value &value) const {
        auto hashValue = hash(value);
        for (auto i = 0; i < numFunctions; ++i) {
            auto uniqueHash = hashValue ^ salts[i];
            auto index = (uniqueHash % size);
            /* Test if the particular bit is set; if it is not set,
             * this value can not have been inserted. */
            if (!(table[index / 8] & (1 << (index % 8)))) {
                return false;
            }
        }
        return true;
    }

    std::vector<char> read() {
        auto copy = table;
        return copy;
    }

    void load(const std::vector<char> &array) {
        table = array;
    }

    friend BloomFilter<Value> &FiltersUnion(const BloomFilter<Value> &first, const BloomFilter<Value> &second);

    friend BloomFilter<Value> &FiltersIntersection(const BloomFilter<Value> &first, const BloomFilter<Value> &second);

private:
    HashFunc hash;
    std::vector<char> table;
    size_t size;
    size_t numFunctions;
    static std::array<size_t, 64> salts;
};

template<typename Value>
std::array<size_t, 64> BloomFilter<Value>::salts = {
        0x1953c322, 0x588ccf17, 0x64bf600c, 0xa6be3f3d,
        0x341a02ea, 0x15b03217, 0x3b062858, 0x5956fd06,
        0x18b5624f, 0xe3be0b46, 0x20ffcd5c, 0xa35dfd2b,
        0x1fc4a9bf, 0x57c45d5c, 0xa8661c4a, 0x4f1b74d2,
        0x5a6dde13, 0x3b18dac6, 0x05a8afbf, 0xbbda2fe2,
        0xa2520d78, 0xe7934849, 0xd541bc75, 0x09a55b57,
        0x9b345ae2, 0xfc2d26af, 0x38679cef, 0x81bd1e0d,
        0x654681ae, 0x4b3d87ad, 0xd5ff10fb, 0x23b32f67,
        0xafc7e366, 0xdd955ead, 0xe7c34b1c, 0xfeace0a6,
        0xeb16f09d, 0x3c57a72d, 0x2c8294c5, 0xba92662a,
        0xcd5b2d14, 0x743936c8, 0x2489beff, 0xc6c56e00,
        0x74a4f606, 0xb244a94a, 0x5edfc423, 0xf1901934,
        0x24af7691, 0xf6c98b25, 0xea25af46, 0x76d5f2e6,
        0x5e33cdf2, 0x445eb357, 0x88556bd2, 0x70d1da7a,
        0x54449368, 0x381020bc, 0x1c0520bf, 0xf7e44942,
        0xa27e2a58, 0x66866fc5, 0x12519ce7, 0x437a8456,
};

template<typename Value>
BloomFilter<Value> &FiltersUnion(const BloomFilter<Value> &first, const BloomFilter<Value> &second) {

}

template<typename Value>
BloomFilter<Value> &FiltersIntersection(const BloomFilter<Value> &first, const BloomFilter<Value> &second) {

}
