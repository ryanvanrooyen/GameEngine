
#include "TestMenu.hpp"
#include "TestColorChangingSquare.hpp"
#include "TestSingleImage.hpp"
#include "TestMultiImages.hpp"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Game::Test
{

TestMenu::~TestMenu()
{
    if (test)
        delete test;
}


void TestMenu::OnUpdate(float deltaTime)
{
    if (test)
        test->OnUpdate(deltaTime);
}


void TestMenu::OnGuiRender()
{
    ImGui::SetNextWindowPos({0.f, 0.f});
    ImGui::Begin("Test");

    if (test)
    {
        test->OnGuiRender();
        ImGui::NewLine();
        if (ImGui::Button("Back##TestMenuBackParent"))
        {
            delete test;
            test = nullptr;
        }
    }
    else
    {
        if (ImGui::Button("Color Changing Square"))
            test = new TestColorChangingSquare();
        if (ImGui::Button("Single Texture"))
            test = new TestSingleImage();
        if (ImGui::Button("Duplicate Textures"))
            test = new TestMultiImages();
        ImGui::NewLine();
    }

    ImGui::Text("%.1f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

}
