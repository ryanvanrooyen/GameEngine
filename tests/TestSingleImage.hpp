
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

class TestSingleImage : public Layer
{
public:
    TestSingleImage();
    const char* LayerName() const override { return "Single Texture"; }
    void OnUpdate(float deltaTime) override;
    void OnGUIRender(Window& window) override;
    ~TestSingleImage() {}

private:
    Shader shader;
    Texture texture;
    VertexBuffer vertexBuffer;
    VertexBufferLayout vertexLayout;
    VertexArray vertexArray;
    IndexBuffer indexBuffer;

    glm::mat4 proj;
    glm::mat4 view;
    glm::vec3 translation;
};

}