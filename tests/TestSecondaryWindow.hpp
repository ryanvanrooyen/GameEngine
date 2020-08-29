
#include "../Engine/core/Layer.hpp"
#include "../Engine/core/Window.hpp"
#include "../Engine/events/Listeners.hpp"
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