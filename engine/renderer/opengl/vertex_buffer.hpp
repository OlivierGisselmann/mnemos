#pragma once

#include <platform/types.hpp>

#include <glad/glad.h>
#include <vector>

namespace Mnemos
{
    class VertexBuffer
    {
    public:
        VertexBuffer();
        ~VertexBuffer();

        void LoadData(const std::vector<f32>& vertices);

        void Bind() const;
        void Unbind() const;

        u32 GetCount() const;

    private:
        u32 mID;
        u32 mCount;
    };
}
