#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

#include <core/logging/logger_manager.hpp>
#include <platform/types.hpp>

namespace fs = std::filesystem;

namespace Mnemos
{
    struct ImageData {
        int width = 0;
        int height = 0;
        int channels = 0;
        std::vector<u8> pixels;

        bool IsValid() const { return !pixels.empty(); }
    };

    class ResourceManager
    {
    public:
        static ResourceManager& Get();

        void SetAssetRoot(const fs::path& path);
        fs::path ResolvePath(const std::string& relativePath);

        const std::string& ReadTextFile(const std::string& relativePath);
        const ImageData& ReadImageFile(const std::string& relativePath);

    private:
        fs::path mAssetRoot;
        std::unordered_map<std::string, std::string> mFileCache;
        std::unordered_map<std::string, ImageData> mImageCache;

        std::string LoadTextFile(const fs::path& fullPath);
        ImageData LoadImageFile(const fs::path& fullPath);
    };
}
