
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
        test = new TestColorChangingSquare();
    if (ImGui::Button("Single Texture"))
        test = new TestSingleImage();
    if (ImGui::Button("Duplicate Textures"))
        test = new TestMultiImages();
    if (ImGui::Button("Secondary Window"))
        test = new TestSecondaryWindow();

    if (test)
    {
        PushListener(test);
        test->OnAttach(window);
    }
}


bool TestMenu::DestroyTest(Window& window)
{
    if (!test)
        return false;

    PopListener(test);
    test->OnDetach(window);
    delete test;
    test = nullptr;
    return true;
}


bool TestMenu::OnKeyPress(Window& window, KeyCode key)
{
    // Allow ESC to be a back button if we have an active test:
    if (key == KeyCode::Escape)
        return DestroyTest(window);
    return false;
}


void TestMenu::OnUpdate(Window& window, float deltaTime)
{
    if (test)
        test->OnUpdate(window, deltaTime);
}


void TestMenu::OnGUIRender(Window& window, float deltaTime)
{
    ImGui::Begin("Test Menu");

    if (test)
    {
        if (ImGui::Button("< Back"))
            DestroyTest(window);
        else
            test->OnGUIRender(window, deltaTime);
    }
    else
    {
        // ImGui::SetNextWindowPos({0.f, 0.f});
        OnGUISelectTest(window);
        ImGui::NewLine();

        if (window.VSyncEnabled())
        {
            if (ImGui::Button("Turn Off VSync"))
                window.SetVSyncEnabled(false);
        }
        else
        {
            if (ImGui::Button("Turn On VSync"))
                window.SetVSyncEnabled(true);
        }

        if (ImGui::Button("Quit"))
            window.Close();
    }

    ImGui::NewLine();
    ImGui::Text("%.1f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

}
