#pragma once

#include <platform/types.hpp>

#include <glad/glad.h>
#include <vector>

namespace Mnemos
{
    class IndexBuffer
    {
    public:
        IndexBuffer(const u32* data, u32 count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        u32 GetCount() const;

    private:
        GLuint mID;
        u32 mCount;
    };
}
