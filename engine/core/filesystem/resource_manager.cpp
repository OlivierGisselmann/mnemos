#include <core/filesystem/resource_manager.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Mnemos
{
    ResourceManager& ResourceManager::Get()
    {
        static ResourceManager instance;
        return instance;
    }

    void ResourceManager::SetAssetRoot(const fs::path& path)
    {
        mAssetRoot = fs::absolute(path);
    }

    fs::path ResourceManager::ResolvePath(const std::string& relativePath)
    {
        fs::path fullPath = mAssetRoot / relativePath;
        return fs::weakly_canonical(fullPath);
    }

    const std::string& ResourceManager::ReadTextFile(const std::string& relativePath)
    {
        // Look for this file in the cache
        auto it = mFileCache.find(relativePath);
        if(it != mFileCache.end())
            return it->second;

        // Create an absolute path
        fs::path fullPath = ResolvePath(relativePath);

        // Read file's content
        std::string content = LoadTextFile(fullPath);

        // Cache the content
        mFileCache[relativePath] = std::move(content);

        return mFileCache[relativePath];
    }

    const ImageData& ResourceManager::ReadImageFile(const std::string& relativePath)
    {
        // Look for this file in the cache
        auto it = mImageCache.find(relativePath);
        if (it != mImageCache.end())
            return it->second;

        // Create an absolute path
        fs::path fullPath = ResolvePath(relativePath);

        // Load file's content
        ImageData img = LoadImageFile(fullPath);

        // Cache the content
        mImageCache[relativePath] = std::move(img);

        return mImageCache[relativePath];
    }

    std::string ResourceManager::LoadTextFile(const fs::path& fullPath)
    {
        // Try to open file
        std::ifstream file(fullPath);
        if(!file.is_open())
        {
            std::cerr << "Couldn't find '" << fullPath << "'\n";
            return "";
        }

        // Read file's content
        std::stringstream buffer;
        buffer << file.rdbuf();

        return buffer.str();
    }

    ImageData ResourceManager::LoadImageFile(const fs::path& fullPath)
    {
        ImageData image;

        // Load image from file
        int width, height, channels;
        u8* data = stbi_load(fullPath.string().c_str(), &width, &height, &channels, 0);
        if (!data) {
            std::cerr << "Failed to load image: '" << fullPath << "'\n";
            return image;
        }

        // Fill struct's values
        image.width = width;
        image.height = height;
        image.channels = channels;
        image.pixels.assign(data, data + (width * height * channels));

        // Free memory
        stbi_image_free(data);
        return image;
    }
}
