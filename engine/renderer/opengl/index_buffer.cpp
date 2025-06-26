#include <renderer/opengl/index_buffer.hpp>

namespace Mnemos
{
    IndexBuffer::IndexBuffer(const u32* data, u32 count) : mCount(count)
    {
        glGenBuffers(1, &mID);

        Bind();

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mCount * sizeof(u32), data, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &mID);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    u32 IndexBuffer::GetCount() const
    {
        return mCount;
    }
}
