#include <renderer/opengl/mesh.hpp>

namespace Mnemos
{
    Mesh::Mesh(const void* vertices, u32 vertexSize, u32 vertexCount, const u32* indices, u32 indexCount)
    : vbo(vertices, vertexSize * vertexCount), ebo(indices, indexCount)
    {
        vao.Bind();
        vbo.Bind();
        ebo.Bind();

        // Enable vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(f32)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(f32)));
        glEnableVertexAttribArray(2);

        vao.Unbind();
    }

    void Mesh::Bind() const
    {
        vao.Bind();
    }

    void Mesh::Unbind() const
    {
        vao.Unbind();
    }

    u32 Mesh::GetIndexCount() const
    {
        return ebo.GetCount();
    }
}
