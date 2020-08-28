
#include "../source/core/Layer.hpp"
#include "../source/core/Window.hpp"
#include "../source/events/Listeners.hpp"
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

class TestSecondaryWindow : public Layer, public EventListener
{
public:
    TestSecondaryWindow();
    const char* LayerName() const override { return "Secondary Window"; }
    void OnUpdate(float deltaTime) override;
    void OnGUIRender(Window& window) override;
    ~TestSecondaryWindow();

    bool OnKeyPress(Window& window, int key) override;

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
    Window* secondaryWindow = nullptr;
};

}