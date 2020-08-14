
#include "VertexBufferLayout.hpp"

VertexBufferLayout::VertexBufferLayout() : stride(0)
{
}

VertexBufferLayout::~VertexBufferLayout()
{
}

void VertexBufferLayout::PushElement(unsigned int type, unsigned int count)
{
    elements.push_back({type, count, false});
    stride += count * VertexBufferElement::GetSizeOfType(type);
}
