
#pragma once

class IndexBuffer
{
private:
    unsigned int rendererId;
    unsigned int count;
public:
    IndexBuffer();
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void SetData(const unsigned int* data, unsigned int count);
    void Bind() const;
    void Unbind() const;

    unsigned int GetCount() const { return count; }
};
