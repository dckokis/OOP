#include "Vector.h"

#define _USE_MATH_DEFINES

#include <gtest/gtest.h>

TEST(EQUAL, ZERO_VECTORS_EQUAL) {
    Vector test_vector1 = Vector(0, 0);
    Vector test_vector2 = Vector(0, 0);
    Vector test_vector3 = Vector(1, 1);
    ASSERT_EQ(test_vector1.x(), test_vector2.x());
    ASSERT_EQ(test_vector1.y(), test_vector2.y());
    ASSERT_FALSE(test_vector1 != test_vector2);
    ASSERT_TRUE(test_vector1 == test_vector2);
    ASSERT_EQ(test_vector1 * test_vector2, 0);
    ASSERT_ANY_THROW(test_vector1.angle(test_vector2));
    ASSERT_ANY_THROW(test_vector3 / 0);
    ASSERT_ANY_THROW(test_vector3 /= 0);
}

TEST(EQUAL, COORD_EQUAL) {
    Vector test_vector1 = Vector(1, 2);
    Vector test_vector2 = Vector(0, 0);
    ASSERT_EQ(test_vector1.x(), 1);
    ASSERT_EQ(test_vector1.y(), 2);
    ASSERT_EQ(test_vector1.angle(), atan(2.0));
    test_vector1.x(2);
    test_vector1.y(1);
    ASSERT_EQ(test_vector1.x(), 2);
    ASSERT_EQ(test_vector1.y(), 1);
    ASSERT_EQ(test_vector1.angle(), atan(0.5));
    test_vector1.x(1);
    test_vector1.y(1);
    ASSERT_EQ(test_vector1.module2(), 2);
    ASSERT_EQ(test_vector2.module2(), 0);
    ASSERT_EQ(test_vector1.angle(), atan(1.0));
}

TEST(OPERATORS, SELF_APPROPRIATION) {
    Vector test_vector1 = Vector(1, 1);
    Vector test_vector2 = Vector(2, 2);
    Vector test_vector3 = Vector(-1, -1);
    ASSERT_EQ(test_vector1 *= 2, test_vector2);
    test_vector1.x(1);
    test_vector1.y(1);
    ASSERT_TRUE((test_vector1 += test_vector1) == test_vector2);
    test_vector1.x(1);
    test_vector1.y(1);
    ASSERT_TRUE((test_vector2 -= test_vector1) == test_vector1);
    test_vector2.x(2);
    test_vector2.y(2);
    ASSERT_TRUE((test_vector2 /= 2) == test_vector1);
    ASSERT_ANY_THROW(test_vector2 /= 0);
    ASSERT_TRUE(-test_vector1 == test_vector3);
}

TEST(OPERATORS, ARITHMETIC) {
    Vector test_vector1 = Vector(1, 1);
    Vector test_vector2 = Vector(2, 2);
    Vector test_vector3 = Vector(-1, -1);
    Vector test_vector4 = Vector();
    ASSERT_TRUE(test_vector1 - test_vector2 == test_vector3);
    ASSERT_EQ(test_vector1 * test_vector2, 4);
    ASSERT_EQ(test_vector1 * 2, test_vector2);
    ASSERT_EQ(test_vector2 / 2, test_vector1);
    ASSERT_ANY_THROW(test_vector1 / 0);
    ASSERT_EQ(test_vector1 + test_vector3, test_vector4);
}