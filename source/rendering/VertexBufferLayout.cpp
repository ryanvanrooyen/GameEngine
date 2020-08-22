
#include "VertexBufferLayout.hpp"
#include "../logging.h"
#include "opengl.hpp"


unsigned int VertexBufferElement::GetSizeOfType(unsigned int type)
{
    switch (type)
    {
        case GL_FLOAT:          return sizeof(GLfloat);
        case GL_UNSIGNED_INT:   return sizeof(GLuint);
        case GL_UNSIGNED_BYTE:  return sizeof(GLbyte);
    }
    ASSERT(false, "Invalid vertex element type: %d", type);
    return 0;
};


void VertexBufferLayout::PushElement(unsigned int type, unsigned int count)
{
    elements.push_back({type, count, false});
    stride += count * VertexBufferElement::GetSizeOfType(type);
}


void VertexBufferLayout::PushFloat(unsigned int count) { PushElement(GL_FLOAT, count); }
void VertexBufferLayout::PushInt(unsigned int count) { PushElement(GL_UNSIGNED_INT, count); }
void VertexBufferLayout::PushByte(unsigned int count) { PushElement(GL_UNSIGNED_BYTE, count); }
