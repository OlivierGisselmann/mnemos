#include <gtest/gtest.h>

#include <platform/types.hpp>

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

TEST(TypesTest, CheckPrimitiveSize)
{
    ASSERT_EQ(sizeof(i8), 1);
    ASSERT_EQ(sizeof(i16), 2);
    ASSERT_EQ(sizeof(i32), 4);
    ASSERT_EQ(sizeof(i64), 8);

    ASSERT_EQ(sizeof(u8), 1);
    ASSERT_EQ(sizeof(u16), 2);
    ASSERT_EQ(sizeof(u32), 4);
    ASSERT_EQ(sizeof(u64), 8);

    ASSERT_EQ(sizeof(f32), 4);
    ASSERT_EQ(sizeof(f64), 8);
}