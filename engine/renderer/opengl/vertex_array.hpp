#pragma once

#include <platform/types.hpp>
#include <renderer/opengl/index_buffer.hpp>
#include <renderer/opengl/vertex_buffer.hpp>

#include <glad/glad.h>

namespace Mnemos
{
    class VertexArray
    {
    public:
        VertexArray(const std::vector<u32>& indices, const std::vector<f32>& vertices);
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

        u32 GetIndicesCount() const;
        u32 GetVerticesCount() const;

    private:
        u32 mID;
        IndexBuffer mIndices;
        VertexBuffer mVertices;
    };
}
