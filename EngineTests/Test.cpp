
#include "Test.hpp"
#include "TestMenu.hpp"
#include "imgui.h"

namespace Game
{

void Test::BackToMenu(Window& window)
{
    if (menu)
        menu->SetChildTest(window, nullptr);
}

void Test::OnGUIRender(Window& window, float deltaTime)
{
    ImGui::Begin(LayerName());
    if (ImGui::Button("< Back"))
    {
        ImGui::End();
        BackToMenu(window);
        return;
    }

    OnTestGUI(window, deltaTime);

    ImGui::NewLine();
    ImGui::Text("%.1f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

}