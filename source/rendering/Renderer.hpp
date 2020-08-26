
#pragma once

namespace Game
{

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer
{
public:
    // Standard drawing commands:
    static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

    // GUI drawing commands:
    static void BeginGUI();
    static void EndGUI();
};
}