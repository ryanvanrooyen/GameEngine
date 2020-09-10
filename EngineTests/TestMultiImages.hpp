
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

class TestMultiImages : public Test
{
public:
    TestMultiImages();
    const char* LayerName() const override { return "Duplicate Textures"; }
    void OnUpdate(Window& window, float deltaTime) override;
    void OnTestGUI(Window& window, float deltaTime) override;

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