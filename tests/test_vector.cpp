#include <gtest/gtest.h>

#include <coriolis/math/vector.hpp>
#include <cmath>

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

TEST(Vector3Test, DotProductSameVector) {
    coriolis::Vector3 v1(3, 4, 0);
    coriolis::Vector3 v2(3, 4, 0);
    real dot_product = v1 ^ v2;

    EXPECT_DOUBLE_EQ(dot_product, 25);
}

TEST(Vector3Test, DotProductOpposingVectors) {
    coriolis::Vector3 v1(3, 4, 0);
    coriolis::Vector3 v2(-3, -4, 0);
    real dot_product = v1 ^ v2;

    EXPECT_DOUBLE_EQ(dot_product, -25);
}

TEST(Vector3Test, BasisFromTwoVectors) {
    coriolis::Vector3 v1(3, 4, 0);
    coriolis::Vector3 v2(-3, -4, 0);

    std::optional<coriolis::Basis3> basis { coriolis::Vector3::basis_from(v1, v2) };

    GTEST_ASSERT_TRUE(basis.has_value());
    GTEST_ASSERT_EQ(basis->i,v1);
    GTEST_ASSERT_EQ(basis->i.angle_between(basis->j),M_PI_2);
    GTEST_ASSERT_EQ(basis->i.angle_between(basis->k),M_PI_2);
    GTEST_ASSERT_EQ(basis->j.angle_between(basis->k),M_PI_2);

    GTEST_ASSERT_FALSE(basis->i == basis->j);
    GTEST_ASSERT_FALSE(basis->i == basis->k);
    GTEST_ASSERT_FALSE(basis->j == basis->k);
}

TEST(Vector3Test, AngleBetween) {
    coriolis::Vector3 v1 { 0.0, 1.0, 1.0 };
    coriolis::Vector3 v2 { 0.0, -1.0, 1.0 };

    real angle = v1.angle_between(v2);

    GTEST_ASSERT_EQ(M_PI_2, angle);
}


TEST(Vector3Test, AngleBetweenSameVectors) {
    coriolis::Vector3 v1 { 1.0, 1.0, 1.0 };
    coriolis::Vector3 v2 { 1.0, 1.0, 1.0 };

    real angle = v1.angle_between(v2);
    GTEST_ASSERT_TRUE(isnan(angle));
}

TEST(Vector3Test, VectorAddition) {
    coriolis::Vector3 v1 { 1,1,1 };
    coriolis::Vector3 v2 { 1,1,1 };

    coriolis::Vector3 actual = v1 + v2;

    coriolis::Vector3 expected { 2, 2, 2 };

    GTEST_ASSERT_EQ(expected,actual);
}
