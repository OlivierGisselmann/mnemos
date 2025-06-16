#include <gtest/gtest.h>

#include <core/filesystem/filesystem.hpp>

TEST(FileSystemTest, ReadsFileContent)
{
    const std::string content = Mnemos::ReadFile("./mock_file.txt");

    EXPECT_EQ(content, "File is good!");
}