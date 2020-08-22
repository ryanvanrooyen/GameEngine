
#include "TestMultiImages.hpp"
#include "../source/rendering/Renderer.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace test
{

TestMultiImages::TestMultiImages()
    : shader("shaders/vertexShader.glsl", "shaders/fragmentTextureShader.glsl")
    , texture("resources/logo3.png")
    , proj(glm::ortho(0.f, 960.f, 0.f, 540.f, -1.f, 1.f))
    , view(glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0)))
    , translation1(200, 200, 0)
    , translation2(0, 0, 0)
{
    shader.Compile();
    shader.Bind();
    shader.SetUniform1i("u_Texture", 0);

    texture.Bind();

    float positions[] = {
        0.f,   0.f, 0.f, 0.f,
        100.f, 0.f, 1.f, 0.f,
        100.f, 100.f, 1.f, 1.f,
        0.f,   100.f, 0.f, 1.f,
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


void TestMultiImages::OnRender(const Renderer& renderer)
{
    glm::mat4 model1 = glm::translate(glm::mat4(1.f), translation1);
    glm::mat4 mvp1 = proj * view * model1;

    glm::mat4 model2 = glm::translate(glm::mat4(1.f), translation2);
    glm::mat4 mvp2 = proj * view * model2;

    shader.Bind();
    shader.SetUniformMat4f("u_MVP", mvp1);
    renderer.Draw(vertexArray, indexBuffer, shader);

    shader.Bind();
    shader.SetUniformMat4f("u_MVP", mvp2);
    renderer.Draw(vertexArray, indexBuffer, shader);
}


void TestMultiImages::OnGuiRender()
{
    ImGui::PushItemWidth(-1);
    ImGui::TextUnformatted("Position 1:");
    ImGui::SliderFloat("##X1", &translation1.x, 0.f, 960.f, "X: %.0f");
    ImGui::SliderFloat("##Y1", &translation1.y, 0.f, 540.f, "Y: %.0f");
    ImGui::TextUnformatted("Position 2:");
    ImGui::SliderFloat("##X2", &translation2.x, 0.f, 960.f, "X: %.0f");
    ImGui::SliderFloat("##Y2", &translation2.y, 0.f, 540.f, "Y: %.0f");
    ImGui::PopItemWidth();
}

}
