#include "VertexBuffer.h"

#include <glad/glad.h>

namespace Saddle {

VertexBuffer::VertexBuffer(unsigned int size)
{
    m_Size = size;
    glCreateBuffers(1, &m_VertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(unsigned int size, void* data)
{
    m_Size = size;
    m_Data = data;
    glCreateBuffers(1, &m_VertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_VertexBufferID); }

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID); }
void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VertexBuffer::SetData(unsigned int size, void* data)
{
    m_Data = data;
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

}