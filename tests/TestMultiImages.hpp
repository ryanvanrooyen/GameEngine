
#include "../source/core/Layer.hpp"
#include "../source/rendering/Shader.hpp"
#include "../source/rendering/Texture.hpp"
#include "../source/rendering/VertexBuffer.hpp"
#include "../source/rendering/VertexBufferLayout.hpp"
#include "../source/rendering/VertexArray.hpp"
#include "../source/rendering/IndexBuffer.hpp"
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
    void OnGuiRender() override;
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