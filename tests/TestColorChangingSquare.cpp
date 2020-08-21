
#include "TestColorChangingSquare.hpp"
#include "../source/rendering/Renderer.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace test
{

TestColorChangingSquare::TestColorChangingSquare()
    : shader("shaders/vertexShader.glsl", "shaders/fragmentColorShader.glsl")
    , proj(glm::ortho(0.f, 960.f, 0.f, 540.f, -1.f, 1.f))
    , view(glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0)))
    , translation(200, 200, 0)
{
    shader.Compile();
    shader.Bind();
    shader.SetUniform1i("u_Texture", 0);

    float positions[] = {
        0.f,   0.f, 0.f, 0.f,
        100.f, 0.f, 1.f, 0.f,
        100.f, 100.f, 1.f, 1.f,
        0.f,   100.f, 0.f, 1.f,
    };

    vertexBuffer.SetData(positions, 4 * 4 * sizeof(float));

    vertexLayout.Push<float>(2); // 2D Position
    vertexLayout.Push<float>(2); // 2D Texture Position

    vertexArray.AddBuffer(vertexBuffer, vertexLayout);

    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0,
    };

    indexBuffer.SetData(indicies, 6);
}


void TestColorChangingSquare::OnRender(const Renderer& renderer)
{
    glm::mat4 model = glm::translate(glm::mat4(1.f), translation);
    glm::mat4 mvp = proj * view * model;

    if (redColor > 1.f || redColor < 0.f)
        increment = -increment;
    redColor += increment;

    shader.Bind();
    shader.SetUniformMat4f("u_MVP", mvp);
    shader.SetUniform4f("u_Color", redColor, 0.3f, 0.8f, 1.f);

    renderer.Draw(vertexArray, indexBuffer, shader);
}


void TestColorChangingSquare::OnGuiRender()
{
    ImGui::Begin("Test");
    ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 960.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

}
