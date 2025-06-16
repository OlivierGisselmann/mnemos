#include <renderer/opengl/texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

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

        // Load image file
        int width, height, channels;
        u8* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        if(data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        stbi_image_free(data);
    }

    Texture::~Texture()
    {

    }

    void Texture::Bind() const
    {
        glBindTexture(GL_TEXTURE_2D, mID);
    }
}
