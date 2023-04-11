#pragma once

#include <vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BufferLayout.h"

namespace Saddle {

class VertexArray {
public:
    VertexArray();
    VertexArray(VertexBuffer* vertex_buffer, IndexBuffer* index_buffer);
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

    void AddVertexBuffer(VertexBuffer* vertex_buffer);
    void SetIndexBuffer(IndexBuffer* index_buffer);

    std::vector<VertexBuffer*> GetVertexBuffer() const { return m_VertexBuffers; }
    IndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; }

private:
    uint32_t m_VertexArrayID;

    std::vector<VertexBuffer*> m_VertexBuffers;
    IndexBuffer* m_IndexBuffer;
};

}