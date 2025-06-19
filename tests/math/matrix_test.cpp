#include <gtest/gtest.h>

#include <math/matrix.hpp>

TEST(MatrixTest, MatrixConstruction)
{
    Mnemos::mat4<f32> mat1;
    Mnemos::mat4<f32> mat2;

    mat2(3, 1) = 55.2f;

    Mnemos::mat4<f32> mat3(mat2);

    EXPECT_FLOAT_EQ(mat1(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(mat1(0, 1), 0.0f);
    EXPECT_FLOAT_EQ(mat2(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(mat3(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(mat3(3, 1), 55.2f);
}

TEST(MatrixTest, MatrixDataAccess)
{
    Mnemos::mat4<f32> mat;

    EXPECT_FLOAT_EQ(mat(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(mat(0, 1), 0.0f);

    mat(2, 4) = 19.5f;

    EXPECT_FLOAT_EQ(mat(2, 4), 19.5f);
}

TEST(MatrixTest, MatrixArithmeticOperations)
{
    // Addition
    Mnemos::mat4<f32> m1;
    Mnemos::mat4<f32> m2;
    Mnemos::mat4<f32> m3 = m1 + m2;
    m2 += m1;

    EXPECT_FLOAT_EQ(m3(0, 0), 2.0f);
    EXPECT_FLOAT_EQ(m3(0, 1), 0.0f);
    EXPECT_FLOAT_EQ(m2(0, 0), 2.0f);
    EXPECT_FLOAT_EQ(m2(0, 1), 0.0f);

    // Substraction
    Mnemos::mat4<f32> m4;
    Mnemos::mat4<f32> m5;
    m5(0, 3) = 5.f;
    Mnemos::mat4<f32> m6 = m4 - m5;
    m4 -= m5;

    EXPECT_FLOAT_EQ(m6(0, 0), 0.0f);
    EXPECT_FLOAT_EQ(m6(0, 1), 0.0f);
    EXPECT_FLOAT_EQ(m6(0, 3), -5.0f);
    EXPECT_FLOAT_EQ(m4(0, 0), 0.0f);

    // Multiplication
    Mnemos::mat4<f32> m7;
    Mnemos::mat4<f32> m8(4.f);
    m7(3, 3) = 5.f;
    Mnemos::mat4<f32> m9 = m7 * m8;
    m7 *= m8;

    EXPECT_FLOAT_EQ(m9(0, 0), 4.0f);
    EXPECT_FLOAT_EQ(m9(0, 1), 0.0f);
    EXPECT_FLOAT_EQ(m9(3, 3), 20.0f);
    EXPECT_FLOAT_EQ(m7(3, 3), 20.0f);
    EXPECT_FLOAT_EQ(m7(0, 3), 0.0f);
    EXPECT_FLOAT_EQ(m7(0, 0), 4.0f);
}

TEST(MatrixTest, MatrixScale)
{
    Mnemos::mat4<f32> scale;
    Mnemos::vec3<f32> factor(3.f);

    scale = Mnemos::Scale(scale, factor);

    EXPECT_FLOAT_EQ(scale(0, 0), 3.0f);
    EXPECT_FLOAT_EQ(scale(1, 1), 3.0f);
    EXPECT_FLOAT_EQ(scale(2, 2), 3.0f);
    EXPECT_FLOAT_EQ(scale(3, 3), 1.0f);
}

TEST(MatrixTest, MatrixRotate)
{
    Mnemos::mat4<f32> rotate(1.f);
    Mnemos::vec3<f32> axis(0.f, 1.f, 0.f);
    f32 angle = 90.0f;

    rotate = Mnemos::Rotate(rotate, angle, axis);
}

TEST(MatrixTest, MatrixTranslate)
{
    Mnemos::mat4<f32> translate;
    Mnemos::vec3<f32> pos(3.f);

    translate = Mnemos::Translate(translate, pos);

    EXPECT_FLOAT_EQ(translate(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(translate(0, 3), 3.0f);
    EXPECT_FLOAT_EQ(translate(1, 3), 3.0f);
    EXPECT_FLOAT_EQ(translate(2, 3), 3.0f);
}
