
#pragma once

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

struct GLFWwindow;

class Renderer
{
private:
    GLFWwindow* window;
    Renderer(GLFWwindow* window);
    friend class Engine;

public:
    // Standard drawing commands:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void SwapBuffers();

    // GUI drawing commands:
    void BeginGUI();
    void EndGUI();
};
