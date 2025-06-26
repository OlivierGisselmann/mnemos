#pragma once

#include <math/matrix.hpp>
#include <renderer/vertex.hpp>
#include <renderer/opengl/vertex_array.hpp>
#include <renderer/opengl/vertex_buffer.hpp>
#include <renderer/opengl/index_buffer.hpp>

namespace Mnemos
{
    struct Mesh
    {
        VertexArray vao;
        VertexBuffer vbo;
        IndexBuffer ebo;

        Mesh(const void* vertices, u32 vertexSize, u32 vertexCount, const u32* indices, u32 indexCount);

        void Bind() const;
        void Unbind() const;
        u32 GetIndexCount() const;
    };
}
