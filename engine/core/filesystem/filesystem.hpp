#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>

namespace Mnemos
{
     std::filesystem::path ResolvePath(const std::filesystem::path& inputPath, const std::filesystem::path& basepath);
     const std::string GetCurrentDir();
     const std::string ReadFile(const char* filePath);
}
