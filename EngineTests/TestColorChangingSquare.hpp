
#include "Test.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/Texture.hpp"
#include "Rendering/VertexBuffer.hpp"
#include "Rendering/VertexBufferLayout.hpp"
#include "Rendering/VertexArray.hpp"
#include "Rendering/IndexBuffer.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace Game
{

class TestColorChangingSquare : public Test
{
public:
    TestColorChangingSquare();
    const char* LayerName() const override { return "Color Changing Square"; }
    void OnUpdate(Window& window, float deltaTime) override;
    void OnTestGUI(Window& window, float deltaTime) override;

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
};

}