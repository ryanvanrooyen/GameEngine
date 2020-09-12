
#pragma once

namespace Game
{

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer
{
public:
    static void Clear();
    static void EnableAlphaBlending();

    // Standard drawing commands:
    static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
};
}