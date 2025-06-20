#pragma once

#include <platform/types.hpp>

#include <glad/glad.h>
#include <vector>

namespace Mnemos
{
    class IndexBuffer
    {
    public:
        IndexBuffer();
        ~IndexBuffer();

        void LoadData(const std::vector<u32>& indices);

        void Bind() const;
        void Unbind() const;

        u32 GetCount() const;

    private:
        GLuint mID;
        u32 mCount;
    };
}
