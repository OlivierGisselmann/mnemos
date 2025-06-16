#include <renderer/opengl/vertex_array.hpp>

#include <iostream>

namespace Mnemos
{
    u32 vbo, ebo;

    VertexArray::VertexArray(const std::vector<u32>& indices, const std::vector<f32>& vertices)
    {
        glGenVertexArrays(1, &mID);
        glBindVertexArray(mID);

        mIndices.LoadData(indices);
        mVertices.LoadData(vertices);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &mID);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(mID);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }
}
