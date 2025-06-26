#pragma once

#include <platform/types.hpp>
#include <renderer/vertex.hpp>

#include <glad/glad.h>

namespace Mnemos
{
    class VertexBuffer
    {
    public:
        VertexBuffer(const void* data, u32 size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

    private:
        u32 mID;
    };
}
