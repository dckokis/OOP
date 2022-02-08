#pragma once

#include <vector>
#include <array>

namespace BloomFilterNamespace {
    class BloomExceptions final : std::exception {
    private:
        std::string m_error;
    public:
        explicit BloomExceptions(std::string error) : m_error(std::move(error)) {}

        [[nodiscard]] const char *what() const noexcept override {
            return m_error.c_str();
        }
    };

    namespace {
        const std::array<size_t, 64> salts = {
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
    }

    template<typename Value>
    class BaseFilter {
    public:
        virtual void insert(const Value &value) = 0;

        virtual bool query(const Value &value) = 0;

        virtual void read(std::vector<unsigned char> &array) = 0;

        virtual void load(std::vector<unsigned char> &array) = 0;

        virtual BaseFilter<Value> *BloomFiltersUnion(BaseFilter *filter2) = 0;

        virtual BaseFilter<Value> *BloomFiltersIntersection(BaseFilter *filter2) = 0;

        virtual ~BaseFilter() = default;

    };

    template<typename Value>
    class NULLbloom final : public BaseFilter<Value> {
    public:
        NULLbloom() = default;;

        ~NULLbloom() = default;;

        void insert(const Value &) override {}

        bool query(const Value &) override { return false; }

        void read(std::vector<unsigned char> &) override {}

        void load(std::vector<unsigned char> &) override {}

        BaseFilter<Value> *BloomFiltersUnion(BaseFilter<Value> *) override { return new NULLbloom(); }

        BaseFilter<Value> *BloomFiltersIntersection(BaseFilter<Value> *) override { return new NULLbloom(); }
    };

    template<typename Value, typename Hash = std::hash<Value>>
    class bloomFilter final : public BaseFilter<Value> {
    public:
        bloomFilter() = default;

        bloomFilter(size_t size_, size_t numFunctions_) : size(size_) {
            if (numFunctions_ <= salts.size()) {
                table = std::vector<unsigned char>(((size_ + 7) / 8), 0);
                numFunctions = numFunctions_;
            } else {
                throw BloomExceptions("numFunctions is bigger than 64");
            }
        }

        ~bloomFilter() = default;

        void insert(const Value &value) override {
            auto hashValue = hashFunc(value);
            for (auto i = 0; i < numFunctions; ++i) {
                auto uniqueHash = hashValue ^ salts[i];
                auto index = (uniqueHash % size);
                table[index / 8] |= (1 << (index % 8));
            }
        }

        bool query(const Value &value) override {
            auto hashValue = hashFunc(value);
            for (auto i = 0; i < numFunctions; ++i) {
                auto uniqueHash = hashValue ^ salts[i];
                auto index = (uniqueHash % size);
                if (!(table[index / 8] & (1 << (index % 8)))) {
                    return false;
                }
            }
            return true;
        }

        void read(std::vector<unsigned char> &array) override {
            const int arraySize = (size + 7) / 8;
            std::copy(table.begin(), table.begin() + arraySize, array.begin());
        }

        void load(std::vector<unsigned char> &array) override{
            table = array;
        }

        BaseFilter<Value> *BloomFiltersUnion(BaseFilter<Value> *another) override {
            auto filter2 = dynamic_cast<bloomFilter<Value> *>(another);
            if ((numFunctions == filter2->getNumFunctions()) && (size == filter2->tableSize())) {
                return fillWith<true>(filter2);
            } else {
                return new NULLbloom<Value>;
            }
        }

        BaseFilter<Value> *
        BloomFiltersIntersection(BaseFilter<Value> *another) override {
            auto filter2 = dynamic_cast<bloomFilter<Value> *>(another);
            if ((numFunctions == filter2->getNumFunctions()) && (size == filter2->tableSize())) {
                return fillWith<false>(filter2);
            } else {
                return new NULLbloom<Value>;
            }
        }

        [[nodiscard]] unsigned int tableSize() const {
            return size;
        }

        [[nodiscard]] unsigned int getNumFunctions() const {
            return numFunctions;
        }

        std::vector<unsigned char> &getTable() {
            return table;
        }

    private:
        inline static constexpr Hash hashFunc = Hash();
        std::vector<unsigned char> table;
        size_t size{};
        size_t numFunctions{};

        template<bool WithUnion>
        bloomFilter<Value> *fillWith(bloomFilter<Value> *second) {
            auto result = new bloomFilter<Value>(size, numFunctions);
            auto arraySize = (size + 7) / 8;
            for (auto i = 0; i < arraySize; ++i) {
                if (WithUnion) {
                    result->getTable()[i] = getTable()[i] | second->getTable()[i];
                } else {
                    result->getTable()[i] = getTable()[i] & second->getTable()[i];
                }

            }
            return result;
        }
    };
}