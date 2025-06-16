#pragma once
#include <core/filesystem/filesystem.hpp>
#include <platform/types.hpp>

#include <glad/glad.h>

namespace Mnemos
{
    class Texture
    {
    public:
        Texture(const std::string& path);
        ~Texture();

        void Bind() const;

    private:
        u32 mID;
    };
}
