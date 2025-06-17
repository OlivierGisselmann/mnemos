#include <gtest/gtest.h>

#include <math/vector.hpp>

TEST(Vector2Test, Vector2Addition)
{
    Mnemos::vec2<float> vec1(3.f, 5.f);
    Mnemos::vec2<float> vec2(-3.f, 6.f);

    Mnemos::vec2<float> vec3 = vec1 + vec2;

    EXPECT_EQ(vec3.x, 0.f);
    EXPECT_EQ(vec3.y, 11.f);
}

TEST(Vector2Test, Vector2Substraction)
{
    Mnemos::vec2<float> vec1(7.f, 5.f);
    Mnemos::vec2<float> vec2(3.f, 6.f);

    Mnemos::vec2<float> vec3 = vec1 - vec2;

    EXPECT_EQ(vec3.x, 4.f);
    EXPECT_EQ(vec3.y, -1.f);
}

TEST(Vector2Test, Vector2Length)
{
    Mnemos::vec2<float> vec(3.f, 4.5f);

    EXPECT_NEAR(vec.length(), 5.408326f, 0.0001f);
}

TEST(Vector2Test, Vector2Dot)
{
    Mnemos::vec2<float> vecX(3.f, 4.5f);
    Mnemos::vec2<float> vecY(3.f, 4.5f);

    EXPECT_FLOAT_EQ(dot(vecX, vecY), 29.25f);
}

TEST(Vector3Test, Vector3Addition)
{
    Mnemos::vec3<float> vec1(3.f, 5.f, -2.5f);
    Mnemos::vec3<float> vec2(-3.f, 6.f, 1.5f);

    Mnemos::vec3<float> vecR = vec1 + vec2;

    EXPECT_EQ(vecR.x, 0.f);
    EXPECT_EQ(vecR.y, 11.f);
    EXPECT_EQ(vecR.z, -1.f);
}

TEST(Vector3Test, Vector3Substraction)
{
    Mnemos::vec3<float> vec1(3.f, 5.f, -2.5f);
    Mnemos::vec3<float> vec2(-3.f, 6.f, 1.5f);

    Mnemos::vec3<float> vecR = vec1 - vec2;

    EXPECT_EQ(vecR.x, 6.f);
    EXPECT_EQ(vecR.y, -1.f);
    EXPECT_EQ(vecR.z, -4.f);
}

TEST(Vector3Test, Vector3Length)
{
    Mnemos::vec3<float> vec(3.f, 4.5f, -10.0f);

    EXPECT_NEAR(vec.length(), 11.369f, 0.001f);
}

TEST(Vector3Test, Vector3Dot)
{
    Mnemos::vec3<float> vec1(3.f, 5.f, -2.5f);
    Mnemos::vec3<float> vec2(-3.f, 6.f, 1.5f);

    EXPECT_FLOAT_EQ(dot(vec1, vec2), 17.25f);
}

TEST(Vector3Test, Vector3Cross)
{
    Mnemos::vec3<float> vec1(1.f, 2.f, 3.f);
    Mnemos::vec3<float> vec2(3.f, 4.f, 5.f);

    EXPECT_EQ(cross(vec1, vec2).x, -2.f);
    EXPECT_EQ(cross(vec1, vec2).y, 4.f);
    EXPECT_EQ(cross(vec1, vec2).z, -2.f);
}