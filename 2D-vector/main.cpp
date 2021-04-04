#include "Vector.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
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
    ASSERT_ANY_THROW(test_vector3 / 0);
    ASSERT_ANY_THROW(test_vector3 /= 0);
}

TEST(EQUAL, COORD_EQUAL) {
    Vector test_vector1 = Vector(1, 2);
    Vector zero = Vector();

    ASSERT_EQ(test_vector1.x(), 1);
    ASSERT_EQ(test_vector1.y(), 2);

    test_vector1.x(2);
    test_vector1.y(1);
    ASSERT_EQ(test_vector1.x(), 2);
    ASSERT_EQ(test_vector1.y(), 1);

    test_vector1.x(1);
    test_vector1.y(1);
    ASSERT_EQ(test_vector1.module2(), 2);
    ASSERT_EQ(zero.module2(), 0);
}

TEST(OPERATORS, SELF_APPROPRIATION) {
    Vector test_vector1 = Vector(1, 1);
    Vector test_vector2 = Vector(2, 2);
    Vector test_vector3 = Vector(-1, -1);
    Vector zero = Vector();
    // *=
    ASSERT_EQ(test_vector1 *= 2, test_vector2);
    ASSERT_EQ(module2(test_vector1 *= 0), 0);
    // +=
    test_vector1.x(1);
    test_vector1.y(1);
    ASSERT_TRUE((test_vector1 += test_vector1) == test_vector2);
    ASSERT_EQ(test_vector2 += zero, test_vector2);
    // -=
    test_vector1.x(1);
    test_vector1.y(1);
    ASSERT_TRUE((test_vector2 -= test_vector1) == test_vector1);
    // /=
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
    Vector test_vector4 = Vector(3, 3);
    Vector zero = Vector();
    // -
    ASSERT_TRUE(test_vector1 - test_vector2 == test_vector3);
    ASSERT_TRUE((test_vector2 - test_vector1) == -test_vector3);
    ASSERT_TRUE((test_vector1 - zero) == test_vector1);
    // *
    ASSERT_EQ(test_vector1 * test_vector2, 4);
    ASSERT_EQ(test_vector1 * 2, test_vector2);
    // /
    ASSERT_EQ(test_vector2 / 2, test_vector1);
    ASSERT_ANY_THROW(test_vector1 / 0);
    // +
    ASSERT_TRUE((test_vector1 + (-test_vector3)) == zero);
    ASSERT_TRUE((test_vector2 + test_vector1) == test_vector4);

}

TEST(METHODS, ANGLES) {
    Vector test_vector1 = Vector(1, 1);
    Vector test_vector2 = Vector(-1, -1);
    Vector zero = Vector();

    ASSERT_NEAR(test_vector1.angle(test_vector2), M_PI, 0.0001);
    ASSERT_EQ(test_vector1.angle(), atan(1));
    ASSERT_EQ(test_vector2.angle(), atan2(-1, -1));
    ASSERT_ANY_THROW(test_vector1.angle(zero));
    ASSERT_ANY_THROW(zero.angle(zero));
    ASSERT_EQ(Vector(0, 1).angle(), M_PI / 2);
    ASSERT_EQ(Vector(0, -1).angle(), -M_PI / 2);
    ASSERT_EQ(Vector(1, 1).angle(Vector(1, 1)), 0);
    ASSERT_EQ(Vector(1, -1).angle(), -M_PI / 4);
    ASSERT_EQ(Vector(-1, -1).angle(), -M_PI * 3 /4);
    ASSERT_EQ(Vector(-1, 1).angle(), M_PI * 3 /4);
    ASSERT_EQ(Vector(1, -1).angle(Vector(1, 1)), -M_PI / 2);
    ASSERT_EQ(Vector(0, -1).angle(Vector(1, 1)), -M_PI * 3 /4);
    ASSERT_NEAR(Vector(2, 0).angle(Vector(1, 1)), -M_PI / 4, 0.0001);
}

TEST(METHODS, MODULE2) {
    Vector test_vector1 = Vector(1, 1);
    Vector test_vector2 = Vector(-1, -1);
    Vector zero = Vector();

    ASSERT_EQ(test_vector1.module2(), test_vector2.module2());
    ASSERT_EQ(zero.module2(), 0);
    ASSERT_EQ(test_vector1.module2(), (-test_vector1).module2());
}

TEST(METHODS, LENGHT) {
    Vector test_vector1 = Vector(1, 1);
    Vector test_vector2 = Vector(-1, -1);
    Vector zero = Vector();

    ASSERT_EQ(zero.length(), 0);
    ASSERT_EQ(test_vector1.length(), sqrt(2));
    ASSERT_EQ(test_vector2.length(), sqrt(2));
}

TEST(METHODS, PROJECTION) {
    Vector test_vector1 = Vector(1, 1);
    Vector test_vector2 = Vector(-1, -1);
    Vector e1 = Vector(1, 0);
    Vector e2 = Vector(0, 1);
    Vector zero = Vector();

    ASSERT_EQ(zero.projection(e1), 0);
    ASSERT_EQ(zero.projection(e2), 0);
    ASSERT_EQ(test_vector1.projection(e1), 1);
    ASSERT_EQ(test_vector1.projection(e2), 1);
    ASSERT_EQ(test_vector2.projection(e1), -1);
    ASSERT_EQ(test_vector2.projection(e2), -1);
}

TEST(METHODS, ROTATION) {
    Vector test_vector1 = Vector(1, 1);
    Vector test_vector2 = Vector(-1, -1);

    ASSERT_EQ(M_PI / 2, test_vector1.rotate(M_PI / 4).angle());
    ASSERT_EQ(-M_PI / 2, test_vector2.rotate(M_PI / 4).angle());
    ASSERT_EQ(Vector(1, 1).rotate(2).angle(), Vector(-1, -1).angle());
    ASSERT_EQ(Vector(1, -1).rotate(-M_PI / 4).angle(), -M_PI / 2);
    ASSERT_EQ(Vector(0, 1).rotate(M_PI / 2).angle(), M_PI);
    ASSERT_EQ(Vector(0, -1).rotate(-M_PI / 2).angle(), M_PI);
    ASSERT_EQ(Vector(1, sqrt(3)).rotate(M_PI / 4).angle(), M_PI / 3 + M_PI / 4);
    ASSERT_EQ(Vector(2, 0).rotate(M_PI * 3 / 4).angle(), M_PI * 3 / 4);
    ASSERT_EQ(Vector(1, 0).rotate(1).angle(), M_PI / 2);
    ASSERT_EQ(Vector(1, 0).rotate(2).angle(), M_PI);
    ASSERT_EQ(Vector(1, 0).rotate(3).angle(), -M_PI / 2);
    ASSERT_EQ(Vector(1, 0).rotate(4).angle(), 0);
    ASSERT_EQ(Vector(1, 0).rotate(5).angle(), M_PI / 2);
    ASSERT_EQ(Vector(1, 0).rotate(-1).angle(), -M_PI / 2);
    ASSERT_EQ(Vector(1, 0).rotate(-2).angle(), M_PI);
    ASSERT_EQ(Vector(1, 0).rotate(-3).angle(), M_PI / 2);
    ASSERT_EQ(Vector(1, 0).rotate(-4).angle(), 0);
    ASSERT_EQ(Vector(1, 0).rotate(-5).angle(), -M_PI / 2);
    ASSERT_EQ( Vector(1, 1).rotate(1).angle(), M_PI * 3 / 4);
}

TEST(METHODS, TRANSFORMTO) {
    ASSERT_TRUE(Vector(1, 1).transformTo(Vector(0, 1), Vector(1, 0)) == Vector(1, 1));
    ASSERT_TRUE(Vector(1, 1).transformFrom(Vector(0, 1), Vector(1, 0)) == Vector(1, 1));
    ASSERT_ANY_THROW(Vector(1, 1).transformTo(Vector(0, 0), Vector()));
    ASSERT_TRUE(Vector(0, 0).transformTo(Vector(88, 90), Vector(1, 111)) == Vector());
}