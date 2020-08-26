
#pragma once

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

namespace Game
{

class VertexArray
{
private:
    unsigned int rendererId;

public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;
    void AddBuffer(const VertexBuffer& vp, const VertexBufferLayout& layout);
};

}