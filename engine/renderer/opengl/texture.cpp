#include <renderer/opengl/texture.hpp>

#include <iostream>

namespace Mnemos
{
    Texture::Texture(const std::string& path)
    {
        glGenTextures(1, &mID);
        glBindTexture(GL_TEXTURE_2D, mID);

        // Set filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        ImageData data = ResourceManager::Get().ReadImageFile(path);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.width, data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.pixels.data());
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    Texture::~Texture()
    {

    }

    void Texture::Bind() const
    {
        glBindTexture(GL_TEXTURE_2D, mID);
    }
}
