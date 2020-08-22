
#pragma once

#include <vector>

struct VertexBufferElement
{
    unsigned int Type;
    unsigned int Count;
    bool Normalized;
    static unsigned int GetSizeOfType(unsigned int type);
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride = 0;

    void PushElement(unsigned int type, unsigned int count);
public:
    void PushFloat(unsigned int count);
    void PushInt(unsigned int count);
    void PushByte(unsigned int count);

    const std::vector<VertexBufferElement> GetElements() const { return elements; }
    unsigned int GetStride() const { return stride; }
};
