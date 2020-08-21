
#pragma once

class VertexBuffer
{
private:
    unsigned int rendererId;
    unsigned int size;

public:
    VertexBuffer();
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void SetData(const void* data, unsigned int size);
    void Bind() const;
    void Unbind() const;

    unsigned int GetSize() const { return size; }
};
