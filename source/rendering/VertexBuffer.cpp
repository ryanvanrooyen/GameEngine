
#include "VertexBuffer.hpp"
#include "opengl.hpp"

VertexBuffer::VertexBuffer() : size(0)
{
    GLCall(glGenBuffers(1, &rendererId));
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size) : size(size)
{
    GLCall(glGenBuffers(1, &rendererId));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::SetData(const void* data, unsigned int size)
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    this->size = size;
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &rendererId));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererId));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
