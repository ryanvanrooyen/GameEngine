
#include "TestMenu.hpp"
#include "TestColorChangingSquare.hpp"
#include "TestSingleImage.hpp"
#include "TestMultiImages.hpp"
#include "TestSecondaryWindow.hpp"
#include "imgui.h"


namespace Game::Test
{

TestMenu::~TestMenu()
{
    if (test)
        delete test;
}


void TestMenu::OnAttach(Window& window)
{
    parentWindow = &window;
}


void TestMenu::OnDetach(Window& window)
{
    parentWindow = nullptr;
}


bool TestMenu::OnKeyPress(Window& window, int key)
{
    // Allow ESC to be a back button if we have an active test:
    if (test && key == 256)  {
        SetChildTest(nullptr);
        return true;
    }
    return false;
}


void TestMenu::SetChildTest(Layer* newTest)
{
    if (!parentWindow)
        return;
    if (!test && !newTest)
        return;

    if (test)
    {
        parentWindow->PopLayer(test);
        delete test;
    }

    test = newTest;
    parentWindow->PushLayer(test);
}


void TestMenu::OnGUIRender(Window& window)
{
    if (!parentWindow)
        return;

    if (test)
    {
        ImGui::NewLine();
        if (ImGui::Button("Back##TestMenuBackParent"))
        {
            SetChildTest(nullptr);
        }
    }
    else
    {
        // ImGui::SetNextWindowPos({0.f, 0.f});
        std::string imGUIName = parentWindow->Name() + "Test";
        ImGui::Begin(imGUIName.c_str());

        if (ImGui::Button("Color Changing Square"))
            SetChildTest(new TestColorChangingSquare());
        if (ImGui::Button("Single Texture"))
            SetChildTest(new TestSingleImage());
        if (ImGui::Button("Duplicate Textures"))
            SetChildTest(new TestMultiImages());
        if (ImGui::Button("Secondary Window"))
            SetChildTest(new TestSecondaryWindow());
        ImGui::NewLine();

        ImGui::Text("%.1f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
}

}
