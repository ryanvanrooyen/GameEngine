
#include "../Engine/core/Layer.hpp"
#include "../Engine/rendering/Shader.hpp"
#include "../Engine/rendering/Texture.hpp"
#include "../Engine/rendering/VertexBuffer.hpp"
#include "../Engine/rendering/VertexBufferLayout.hpp"
#include "../Engine/rendering/VertexArray.hpp"
#include "../Engine/rendering/IndexBuffer.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace Game::Test
{

class TestColorChangingSquare : public Layer
{
public:
    TestColorChangingSquare();
    const char* LayerName() const override { return "Color Changing Square"; }
    void OnUpdate(float deltaTime) override;
    void OnGUIRender(Window& window) override;
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