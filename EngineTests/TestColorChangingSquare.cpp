
#include "EngineCommon.h"
#include "TestColorChangingSquare.hpp"
#include "Core/Window.hpp"
#include "Input/Input.hpp"
#include "Rendering/Renderer.hpp"
#include "imgui.h"

namespace Game
{

static float width = 100.f;
static float height = 100.f;


TestColorChangingSquare::TestColorChangingSquare()
    : shader("shaders/vertexShader.glsl", "shaders/fragmentColorShader.glsl")
    , proj(glm::ortho(0.f, 960.f, 540.f, 0.f, -1.f, 1.f))
    , view(glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0)))
    , translation(200, 200, 0)
{
    shader.Compile();
    shader.Bind();
    shader.SetUniform1i("u_Texture", 0);

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


bool TestColorChangingSquare::OnWindowResize(Window& window)
{
    proj = glm::ortho(0.f, (float)window.Width(), (float)window.Height(), 0.f, -1.f, 1.f);
    return false;
}


void TestColorChangingSquare::OnAttach(Window& window)
{
    proj = glm::ortho(0.f, (float)window.Width(), (float)window.Height(), 0.f, -1.f, 1.f);
}


void TestColorChangingSquare::OnUpdate(Window& window, float deltaTime)
{
    if (Input::IsKeyPressed(KeyCode::Left))
        translation.x -= 1.f;
    else if (window.IsKeyPressed(KeyCode::Right))
        translation.x += 1.f;

    if (window.IsKeyPressed(KeyCode::Up))
        translation.y -= 1.f;
    else if (window.IsKeyPressed(KeyCode::Down))
        translation.y += 1.f;

    if (window.IsMousePressed(MouseCode::ButtonLeft))
    {
        auto [x, y] = window.GetMousePosition();
        translation.x = x - width/2.f;
        translation.y = y - height/2.f;
    }

    if (translation.x < 0)
        translation.x = 0.f;
    else if (translation.x > window.Width() - width)
        translation.x = window.Width() - width;

    if (translation.y < 0)
        translation.y = 0.f;
    else if (translation.y > window.Height() - height)
        translation.y = window.Height() - height;

    glm::mat4 model = glm::translate(glm::mat4(1.f), translation);
    glm::mat4 mvp = proj * view * model;

    if (redColor > 1.f || redColor < 0.f)
        increment = -increment;
    redColor += increment;

    shader.Bind();
    shader.SetUniformMat4f("u_MVP", mvp);
    shader.SetUniform4f("u_Color", redColor, 0.3f, 0.8f, 1.f);

    Renderer::Draw(vertexArray, indexBuffer, shader);
}


void TestColorChangingSquare::OnGUIRender(Window& window, float deltaTime)
{
    // ImGui::Begin(("##Window_" + window.Name()).c_str());
    ImGui::PushItemWidth(-1);
    ImGui::TextUnformatted("Position:");
    ImGui::SliderFloat(("##X_" + window.Name()).c_str(), &translation.x, 0.f, 960.f - width, "X: %.0f");
    ImGui::SliderFloat(("##Y_" + window.Name()).c_str(), &translation.y, 0.f, 540.f - height, "Y: %.0f");
    ImGui::PopItemWidth();
    // ImGui::End();
}

}
