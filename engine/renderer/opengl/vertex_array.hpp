#pragma once

#include <platform/types.hpp>

#include <glad/glad.h>

namespace Mnemos
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

    private:
        u32 mID;
    };
}
