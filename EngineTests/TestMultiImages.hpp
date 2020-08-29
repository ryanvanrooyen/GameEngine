
#include "../Engine/Core/Layer.hpp"
#include "../Engine/Rendering/Shader.hpp"
#include "../Engine/Rendering/Texture.hpp"
#include "../Engine/Rendering/VertexBuffer.hpp"
#include "../Engine/Rendering/VertexBufferLayout.hpp"
#include "../Engine/Rendering/VertexArray.hpp"
#include "../Engine/Rendering/IndexBuffer.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Game::Test
{

class TestMultiImages : public Layer
{
public:
    TestMultiImages();
    const char* LayerName() const override { return "Duplicate Textures"; }
    void OnUpdate(float deltaTime) override;
    void OnGUIRender(Window& window) override;
    ~TestMultiImages() {}

private:
    Shader shader;
    Texture texture;
    VertexBuffer vertexBuffer;
    VertexBufferLayout vertexLayout;
    VertexArray vertexArray;
    IndexBuffer indexBuffer;

    glm::mat4 proj;
    glm::mat4 view;
    glm::vec3 translation1;
    glm::vec3 translation2;
};

}