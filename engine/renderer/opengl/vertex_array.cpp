#include <renderer/opengl/vertex_array.hpp>

namespace Mnemos
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &mID);
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
