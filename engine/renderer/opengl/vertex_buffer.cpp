#include <renderer/opengl/vertex_buffer.hpp>

namespace Mnemos
{
    VertexBuffer::VertexBuffer()
    {
        
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &mID);
    }

    void VertexBuffer::LoadData(const std::vector<f32>& vertices)
    {
        // Create GPU buffer
        glGenBuffers(1, &mID);

        // Bind buffer
        Bind();

        // Load vertices into buffer
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(f32), vertices.data(), GL_STATIC_DRAW);

        // Enable vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void*)(3 * sizeof(f32)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void*)(6 * sizeof(f32)));
        glEnableVertexAttribArray(2);

        // Get vertices count
        mCount = vertices.size();
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, mID);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    u32 VertexBuffer::GetCount() const
    {
        return mCount;
    }
}
