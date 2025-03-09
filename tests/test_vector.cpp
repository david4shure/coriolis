#include <gtest/gtest.h>

#include <coriolis/math/vector.hpp>

TEST(Vector3Test, Magnitude) {
    coriolis::Vector3 v(3, 4, 0);
    EXPECT_DOUBLE_EQ(v.mag(), 5.0);
}

TEST(Vector3Test, SqrMagnitude) {
    coriolis::Vector3 v(3, 4, 0);
    EXPECT_DOUBLE_EQ(v.sqr_mag(), 25);
}

TEST(Vector3Test, Norm) {
    coriolis::Vector3 v(3, 4, 0);
    v.norm();
    EXPECT_DOUBLE_EQ(v.mag(), 1.0);
}

TEST(Vector3Test, DotProduct) {
    coriolis::Vector3 v1(3, 4, 0);
    coriolis::Vector3 v2(3, 4, 0);
    real dot_product = v1 ^ v2;
    real magnitude = v1.sqr_mag();

    EXPECT_DOUBLE_EQ(dot_product, magnitude);
}
