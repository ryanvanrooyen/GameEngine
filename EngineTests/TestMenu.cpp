
#include "TestMenu.hpp"
#include "Test.hpp"
#include "TestColorChangingSquare.hpp"
#include "TestSingleImage.hpp"
#include "TestMultiImages.hpp"
#include "TestSecondaryWindow.hpp"
#include "imgui.h"


namespace Game
{

void TestMenu::OnGUISelectTest(Window& window)
{
    if (ImGui::Button("Color Changing Square"))
        SetChildTest(window, std::make_shared<TestColorChangingSquare>());
    if (ImGui::Button("Single Texture"))
        SetChildTest(window, std::make_shared<TestSingleImage>());
    if (ImGui::Button("Duplicate Textures"))
        SetChildTest(window, std::make_shared<TestMultiImages>());
    if (ImGui::Button("Secondary Window"))
        SetChildTest(window, std::make_shared<TestSecondaryWindow>());
}


bool TestMenu::OnKeyPress(Window& window, KeyCode key)
{
    // Allow ESC to be a back button if we have an active test:
    if (test && key == KeyCode::Escape)  {
        SetChildTest(window, nullptr);
        return true;
    }
    return false;
}


void TestMenu::SetChildTest(Window& window, const std::shared_ptr<Test>& newTest)
{
    if (!test && !newTest)
        return;

    if (test)
        window.PopLayer(test);

    test = newTest;
    if (test)
    {
        test->menu = this;
        window.PushLayer(test);
    }
}


void TestMenu::OnGUIRender(Window& window, float deltaTime)
{
    if (!test)
    {
        // ImGui::SetNextWindowPos({0.f, 0.f});
        ImGui::Begin("Test Menu");
        OnGUISelectTest(window);
        ImGui::NewLine();

        if (ImGui::Button("Quit"))
            window.Close();

        ImGui::NewLine();
        ImGui::Text("%.1f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
}

}
