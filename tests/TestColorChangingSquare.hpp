
#include "Test.hpp"
#include "../source/rendering/Shader.hpp"
#include "../source/rendering/Texture.hpp"
#include "../source/rendering/VertexBuffer.hpp"
#include "../source/rendering/VertexBufferLayout.hpp"
#include "../source/rendering/VertexArray.hpp"
#include "../source/rendering/IndexBuffer.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{

class TestColorChangingSquare : public Test
{
private:
    Shader shader;
    VertexBuffer vertexBuffer;
    VertexBufferLayout vertexLayout;
    VertexArray vertexArray;
    IndexBuffer indexBuffer;

    float redColor = 0.0f;
    float increment = 0.05f;

    glm::mat4 proj;
    glm::mat4 view;
    glm::vec3 translation;

public:
    TestColorChangingSquare();
    ~TestColorChangingSquare() {}

    void OnGuiRender() override;
    void OnRender() override;
};

}