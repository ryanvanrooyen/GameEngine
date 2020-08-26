
#include "TestSingleImage.hpp"
#include "../source/rendering/Renderer.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Game::Test
{

static float width = 100.f;
static float height = 100.f;


TestSingleImage::TestSingleImage()
    : shader("shaders/vertexShader.glsl", "shaders/fragmentTextureShader.glsl")
    , texture("resources/logo3.png")
    , proj(glm::ortho(0.f, 960.f, 0.f, 540.f, -1.f, 1.f))
    , view(glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0)))
    , translation(200, 200, 0)
{
    shader.Compile();
    shader.Bind();
    shader.SetUniform1i("u_Texture", 0);

    texture.Bind();

    float positions[] = {
        0.f,   0.f, 0.f, 0.f,
        width, 0.f, 1.f, 0.f,
        width, height, 1.f, 1.f,
        0.f,   height, 0.f, 1.f,
    };

    vertexBuffer.SetData(positions, 4 * 4 * sizeof(float));

    vertexLayout.PushFloat(2); // 2D Position
    vertexLayout.PushFloat(2); // 2D Texture Position

    vertexArray.AddBuffer(vertexBuffer, vertexLayout);

    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0,
    };

    indexBuffer.SetData(indicies, 6);
}


void TestSingleImage::OnUpdate(float deltaTime)
{
    glm::mat4 model = glm::translate(glm::mat4(1.f), translation);
    glm::mat4 mvp = proj * view * model;

    shader.Bind();
    shader.SetUniformMat4f("u_MVP", mvp);

    Renderer::Draw(vertexArray, indexBuffer, shader);
}


void TestSingleImage::OnGuiRender()
{
    ImGui::PushItemWidth(-1);
    ImGui::TextUnformatted("Position:");
    ImGui::SliderFloat("##X", &translation.x, 0.f, 960.f - width, "X: %.0f");
    ImGui::SliderFloat("##Y", &translation.y, 0.f, 540.f - height, "Y: %.0f");
    ImGui::PopItemWidth();
}

}
