
#pragma once

#include "opengl.hpp"
#include <vector>

struct VertexBufferElement
{
    unsigned int Type;
    unsigned int Count;
    bool Normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:          return sizeof(GLfloat);
            case GL_UNSIGNED_INT:   return sizeof(GLuint);
            case GL_UNSIGNED_BYTE:  return sizeof(GLbyte);
        }
        ASSERT(false, "Invalid vertex element type: %d", type);
        return 0;
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;

    void PushElement(unsigned int type, unsigned int count);
public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    template<typename T>
    // void Push(unsigned int count) { static_assert(false, "Invalid Vertex Element type for VertextBufferLayout"); }
    void Push(unsigned int count) {}

    template<>
    void Push<float>(unsigned int count) { PushElement(GL_FLOAT, count); }

    template<>
    void Push<unsigned int>(unsigned int count) { PushElement(GL_UNSIGNED_INT, count); }

    template<>
    void Push<unsigned char>(unsigned int count) { PushElement(GL_UNSIGNED_BYTE, count); }

    const std::vector<VertexBufferElement> GetElements() const { return elements; }
    unsigned int GetStride() const { return stride; }
};
