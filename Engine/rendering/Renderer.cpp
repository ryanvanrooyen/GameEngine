
#include "EngineCommon.h"
#include "Renderer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "opengl.hpp"


namespace Game
{

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

}