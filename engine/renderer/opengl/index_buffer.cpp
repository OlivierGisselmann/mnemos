#include <renderer/opengl/index_buffer.hpp>

namespace Mnemos
{
    IndexBuffer::IndexBuffer()
    {
        
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &mID);
    }

    void IndexBuffer::LoadData(const std::vector<u32>& indices)
    {
        // Create GPU Buffer
        glGenBuffers(1, &mID);

        // Bind buffer
        Bind();

        // Load indices into buffer
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32), indices.data(), GL_STATIC_DRAW);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
