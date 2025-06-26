#include <renderer/opengl/vertex_buffer.hpp>

namespace Mnemos
{
    VertexBuffer::VertexBuffer(const void* data, u32 size)
    {
        glGenBuffers(1, &mID);

        Bind();

        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &mID);
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, mID);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
