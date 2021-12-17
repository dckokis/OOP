#include <gtest/gtest.h>
#include "btree.hpp"

class custom {
    double x_{};
    std::string str_{};
public:
    custom() = default;
    explicit custom(double&& x, std::string&& str) : x_(x), str_(str) {}
    bool operator==(const custom& another) const { return x_ == another.x_ && str_ == another.str_; }
    bool operator!=(const custom& another) const { return !(*this == another); }
    bool operator<(const custom& another) const { return x_ < another.x_; }
};

TEST(Constructor, Empty)
{
    btree<int, std::string> t;
    ASSERT_TRUE(t.empty());
    ASSERT_EQ(t.size(), 0);
    ASSERT_TRUE(t.begin() == t.end());
}

TEST(Constructor, CustomComp)
{
    btree<int, std::string> t1;
    t1[3] = "three";
    t1[1] = "one";
    t1[5] = "five";
    std::string buf;
    for (auto i = t1.begin(); i != t1.end(); ++i) {
        buf += i->second;
    }
    ASSERT_EQ(buf, "onethreefive");

    btree<int, std::string, std::greater<>> t2;
    t2[3] = "three";
    t2[1] = "one";
    t2[5] = "five";
    buf.clear();
    for (auto i = t2.begin(); i != t2.end(); ++i) {
        buf += i->second;
    }
    ASSERT_EQ(buf, "fivethreeone");
}

TEST(Constructor, Copy)
{
    btree<std::string, custom> t1;
    t1["Two"] = custom(0.5, "one");
    t1["One"] = custom(0.1, "two");
    t1["Four"] = custom(0.4, "three");
    t1["Three"] = custom(0.11, "five");
    auto t2 = btree<std::string, custom>(t1);
    ASSERT_TRUE(!t2.empty());
    ASSERT_EQ(t2.size(), 4);
    for (auto i = t1.begin(); i != t1.end(); ++i){
        ASSERT_EQ(t1.at(i->first), t2.at(i->first));
    }
}

TEST(Constructor, Move) {
    btree<custom, int> t1;
    const auto key_0 = custom(0, "zero");
    const auto key_1 = custom(0.1, "one");
    const auto key_2 = custom(0.2, "two");
    t1[key_2] = 2;
    t1[key_1] = 1;
    t1[key_0] = 0;
    auto t2 = btree<custom, int>(std::move(t1));
    ASSERT_TRUE(t1.empty());
    ASSERT_EQ(t2[key_2], 2);
    ASSERT_EQ(t2[key_1], 1);
    ASSERT_EQ(t2[key_0], 0);
}

TEST(Operator, CopyAssigment) {
    btree<std::string, std::string> t1;
    t1["One"] = "_one";
    auto& t2 = t1;
    ASSERT_TRUE(!t2.empty());
    ASSERT_EQ(t2.size(), 1);
    ASSERT_EQ((t2.find("One"))->second, "_one");
}

TEST(Operator, MoveAssigment) {
    btree<custom, std::string> t1;
    const auto key_0 = custom(0, "zero");
    const auto key_1 = custom(0.1, "one");
    const auto key_2 = custom(0.2, "two");
    t1[key_2] = "str2";
    t1[key_1] = "str1";
    t1[key_0] = "str0";
    auto t2 = std::move(t1);
    ASSERT_TRUE(t1.empty());
    ASSERT_EQ(t2[key_2], "str2");
    ASSERT_EQ(t2[key_1], "str1");
    ASSERT_EQ(t2[key_0], "str0");

    t1 = std::move(t2);
    ASSERT_TRUE(t2.empty());
    ASSERT_EQ(t1[key_2], "str2");
    ASSERT_EQ(t1[key_1], "str1");
    ASSERT_EQ(t1[key_0], "str0");
}

TEST(Operator, Brackets) {
    const auto key_1 = custom(0.2, "one");
    const auto key_2 = custom(0.1, "zero");
    btree<custom, std::string> t;
    t[key_1] = "_one";
    t[key_2] = "_two";
    t[key_1] = "_three";
    ASSERT_TRUE(!t.empty());
    ASSERT_EQ(t.size(), 2);
    ASSERT_EQ(t[key_1], "_three");
    ASSERT_EQ(t[key_2], "_two");
}