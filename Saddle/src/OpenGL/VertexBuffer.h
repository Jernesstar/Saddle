#pragma once

#include <glad/glad.h>

#include "BufferLayout.h"

namespace Saddle {

class VertexBuffer {
public:
    const BufferLayout Layout;

public:
    template<typename T, std::size_t TCount>
    VertexBuffer(const T (&vertices)[TCount], const BufferLayout& layout)
        : Layout(layout)
    {
        glCreateBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, TCount * Layout.Stride, vertices, GL_DYNAMIC_DRAW);
    }

    VertexBuffer(std::size_t count, const BufferLayout& layout)
        : Layout(layout)
    {
        glCreateBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, count * Layout.Stride, nullptr, GL_DYNAMIC_DRAW);
    }

    ~VertexBuffer() { glDeleteBuffers(1, &m_VertexBufferID); }

    void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID); }
    void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    template<typename T, std::size_t TCount>
    void SetData(const T (&vertices)[TCount])
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, TCount * Layout.Stride, vertices);
    }

    void SetData(const void* data, std::size_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

private:
    uint32_t m_VertexBufferID;
};

}