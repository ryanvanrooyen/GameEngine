
#include "VertexArray.hpp"
#include "opengl.hpp"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &rendererId));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &rendererId));
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(rendererId));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();

    // GLCall(GLint posAttr = glGetAttribLocation(program, "position"));
    // std::cout << "Position Attirbute: " << posAttr << std::endl;

    unsigned long offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const VertexBufferElement& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        unsigned char normalized = element.Normalized ? GL_TRUE : GL_FALSE;
        GLCall(glVertexAttribPointer(i, element.Count, element.Type, normalized, layout.GetStride(), (const void*)offset));
        offset += element.Count * VertexBufferElement::GetSizeOfType(element.Type);
    }
}
