
#include "Core/Layer.hpp"
#include "Core/Window.hpp"
#include "Events/Listeners.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/Texture.hpp"
#include "Rendering/VertexBuffer.hpp"
#include "Rendering/VertexBufferLayout.hpp"
#include "Rendering/VertexArray.hpp"
#include "Rendering/IndexBuffer.hpp"
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