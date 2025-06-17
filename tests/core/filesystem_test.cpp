#include <gtest/gtest.h>

#include <core/filesystem/resource_manager.hpp>

TEST(FileSystemTest, ReadsFileContent)
{
    Mnemos::ResourceManager& resourceManager = Mnemos::ResourceManager::Get();

    resourceManager.SetAssetRoot("./");
    const std::string content = resourceManager.ReadTextFile("mock_file.txt");

    EXPECT_EQ(content, "File is good!");
}