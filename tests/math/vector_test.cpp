#include <gtest/gtest.h>

#include <math/vector.hpp>

TEST(VectorTest, VectorConstruction)
{
    Mnemos::vec3<f32> v1(1.f, 2.f, 3.f);
    Mnemos::vec3<f32> v2 = {1.f, 2.f, 3.f};
    Mnemos::vec3<f32> v3 {1.f, 2.f, 3.f};

    Mnemos::vec3<f32> v4(2.f);
    Mnemos::vec3<f32> v5{2.f};
    Mnemos::vec3<f32> v6 = {2.f};

    Mnemos::vec3<f32> v7(v1);
    Mnemos::vec3<f32> v8{v1};
    Mnemos::vec3<f32> v9 = {v1};

    // 3 value construction
    EXPECT_EQ(v1.x, 1.0f);
    EXPECT_EQ(v1.y, 2.0f);
    EXPECT_EQ(v1.z, 3.0f);
    EXPECT_EQ(v2.x, 1.0f);
    EXPECT_EQ(v2.y, 2.0f);
    EXPECT_EQ(v2.z, 3.0f);
    EXPECT_EQ(v3.x, 1.0f);
    EXPECT_EQ(v3.y, 2.0f);
    EXPECT_EQ(v3.z, 3.0f);

    // 1 value construction
    EXPECT_EQ(v4.x, 2.0f);
    EXPECT_EQ(v4.y, 2.0f);
    EXPECT_EQ(v4.z, 2.0f);
    EXPECT_EQ(v5.x, 2.0f);
    EXPECT_EQ(v5.y, 2.0f);
    EXPECT_EQ(v5.z, 2.0f);
    EXPECT_EQ(v6.x, 2.0f);
    EXPECT_EQ(v6.y, 2.0f);
    EXPECT_EQ(v6.z, 2.0f);

    // Copy construction
    EXPECT_EQ(v7.x, 1.0f);
    EXPECT_EQ(v7.y, 2.0f);
    EXPECT_EQ(v7.z, 3.0f);
    EXPECT_EQ(v8.x, 1.0f);
    EXPECT_EQ(v8.y, 2.0f);
    EXPECT_EQ(v8.z, 3.0f);
    EXPECT_EQ(v9.x, 1.0f);
    EXPECT_EQ(v9.y, 2.0f);
    EXPECT_EQ(v9.z, 3.0f);
}

TEST(VectorTest, VectorArithmeticOperations)
{
    Mnemos::vec3<f32> v(1.f, 2.f, 3.f);
    Mnemos::vec3<f32> v2(2.f);

    // Addition with vector
    Mnemos::vec3<f32> v3 = v + v2;
    EXPECT_EQ(v3.x, 3.0f);
    EXPECT_EQ(v3.y, 4.0f);
    EXPECT_EQ(v3.z, 5.0f);

    // Substraction with vector
    Mnemos::vec3<f32> v4 = v - v2;
    EXPECT_EQ(v4.x, -1.0f);
    EXPECT_EQ(v4.y, 0.0f);
    EXPECT_EQ(v4.z, 1.0f);

    // Division with vector
    Mnemos::vec3<f32> v5 = v / v2;
    EXPECT_EQ(v5.x, 0.5f);
    EXPECT_EQ(v5.y, 1.0f);
    EXPECT_EQ(v5.z, 1.5f);

    // Addition with scalar
    Mnemos::vec3<f32> v6 = v + 2;
    EXPECT_EQ(v6.x, 3.0f);
    EXPECT_EQ(v6.y, 4.0f);
    EXPECT_EQ(v6.z, 5.0f);

    // Substraction with scalar
    Mnemos::vec3<f32> v7 = v - 2;
    EXPECT_EQ(v7.x, -1.0f);
    EXPECT_EQ(v7.y, 0.0f);
    EXPECT_EQ(v7.z, 1.0f);

    // Division with scalar
    Mnemos::vec3<f32> v8 = v / 2;
    EXPECT_EQ(v8.x, 0.5f);
    EXPECT_EQ(v8.y, 1.0f);
    EXPECT_EQ(v8.z, 1.5f);
}

TEST(VectorTest, VectorLength)
{
    Mnemos::vec3<f32> v(2.f);
    f32 length = Mnemos::Length(v);

    EXPECT_NEAR(length, 3.4641016f, 0.0001f);
}

TEST(VectorTest, VectorNormalize)
{
    Mnemos::vec3<f32> v(2.f);
    Mnemos::vec3<f32> v2 = Normalize(v);

    EXPECT_NEAR(v2.x, 0.5773502f, 0.0001f);
    EXPECT_NEAR(v2.y, 0.5773502f, 0.0001f);
    EXPECT_NEAR(v2.z, 0.5773502f, 0.0001f);
}

TEST(VectorTest, VectorDot)
{
    Mnemos::vec3<f32> v1(2.f);
    Mnemos::vec3<f32> v2(4.f);

    f32 dot = Dot(v1, v2);
    EXPECT_FLOAT_EQ(dot, 24.0f);
}

TEST(VectorTest, VectorCross)
{
    Mnemos::vec3<f32> v1(1.f, 2.f, 3.f);
    Mnemos::vec3<f32> v2(3.f, 4.f, 5.f);

    Mnemos::vec3<f32> cross = Cross(v1, v2);
    EXPECT_FLOAT_EQ(cross.x, -2.f);
    EXPECT_FLOAT_EQ(cross.y, 4.f);
    EXPECT_FLOAT_EQ(cross.z, -2.f);
}
