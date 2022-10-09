#pragma once

namespace Saddle {

struct IndexBuffer {
    template<std::size_t Count>
    IndexBuffer(const unsigned int (&indices)[Count])
        : m_Count(Count)
    {
        glCreateBuffers(1, &m_IndexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_IndexBufferID);
        glBufferData(GL_ARRAY_BUFFER, m_Count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    ~IndexBuffer() { glDeleteBuffers(1, &m_IndexBufferID); }

    void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID); }
    void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    const unsigned int GetCount() const { return m_Count; }

private:
    unsigned int m_IndexBufferID;
    unsigned int m_Count;
};

}