
#include "EngineCommon.h"
#include "ImGuiLayer.hpp"
#include "Window.hpp"
#include "examples/imgui_impl_opengl3.h"


namespace Game
{


static void SetDisplaySize(Window& window)
{
    ImGuiIO& io = ImGui::GetIO();

    float windowWidth = window.Width();
    float windowHeight = window.Height();
    auto framebufferSize = window.GetFramebufferSize();
    float framebufferWidth = framebufferSize.first;
    float framebufferHeight = framebufferSize.second;

    io.DisplaySize = ImVec2(windowWidth, windowHeight);
    if (windowWidth > 0.f && windowHeight > 0.f)
        io.DisplayFramebufferScale = ImVec2(framebufferWidth / windowWidth, framebufferHeight / windowHeight);
}


void ImGuiLayer::OnAttach(Window& window)
{
    TRACE("Initializing ImGui");

    ImFontAtlas* atlas = new ImFontAtlas();
    context = ImGui::CreateContext(atlas);
    ASSERT(context, "Failed to create ImGui Context");

    ImGuiIO& io = ImGui::GetIO();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(1.3f);
    io.Fonts->AddFontDefault();
    io.FontGlobalScale = 1.3f;
    io.Fonts->Build();

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    SetDisplaySize(window);

    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
    io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;    // We can create multi-viewports on the Platform side (optional)

    // io.SetClipboardTextFn = ImGui_ImplGlfw_SetClipboardText;
    // io.GetClipboardTextFn = ImGui_ImplGlfw_GetClipboardText;

    // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
    io.KeyMap[ImGuiKey_Tab] = KeyCode::Tab;
    io.KeyMap[ImGuiKey_LeftArrow] = KeyCode::Left;
    io.KeyMap[ImGuiKey_RightArrow] = KeyCode::Right;
    io.KeyMap[ImGuiKey_UpArrow] = KeyCode::Up;
    io.KeyMap[ImGuiKey_DownArrow] = KeyCode::Down;
    io.KeyMap[ImGuiKey_PageUp] = KeyCode::PageUp;
    io.KeyMap[ImGuiKey_PageDown] = KeyCode::PageDown;
    io.KeyMap[ImGuiKey_Home] = KeyCode::Home;
    io.KeyMap[ImGuiKey_End] = KeyCode::End;
    io.KeyMap[ImGuiKey_Insert] = KeyCode::Insert;
    io.KeyMap[ImGuiKey_Delete] = KeyCode::Delete;
    io.KeyMap[ImGuiKey_Backspace] = KeyCode::Backspace;
    io.KeyMap[ImGuiKey_Space] = KeyCode::Space;
    io.KeyMap[ImGuiKey_Enter] = KeyCode::Enter;
    io.KeyMap[ImGuiKey_Escape] = KeyCode::Escape;
    io.KeyMap[ImGuiKey_KeyPadEnter] = KeyCode::KPEnter;
    io.KeyMap[ImGuiKey_A] = KeyCode::A;
    io.KeyMap[ImGuiKey_C] = KeyCode::C;
    io.KeyMap[ImGuiKey_V] = KeyCode::V;
    io.KeyMap[ImGuiKey_X] = KeyCode::X;
    io.KeyMap[ImGuiKey_Y] = KeyCode::Y;
    io.KeyMap[ImGuiKey_Z] = KeyCode::Z;

    const char* glsl_version = "#version 150";
    ImGui_ImplOpenGL3_Init(glsl_version);
}


void ImGuiLayer::OnDetach(Window& window)
{
    TRACE("Shutting down ImGui");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}


void ImGuiLayer::BeginGUI(Window& window, float deltaTime)
{
    // ImGui::SetCurrentContext(context);

    ImGui_ImplOpenGL3_NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    io.DeltaTime = deltaTime;

    // ImGui_ImplGlfw_UpdateMouseCursor();
    // Update game controllers (if enabled and available)
    // ImGui_ImplGlfw_UpdateGamepads();

    ImGui::NewFrame();

    // Temporarily test out the demo window:
    bool show = true;
    ImGui::ShowDemoWindow(&show);
}


void ImGuiLayer::EndGUI(Window& window, float deltaTime)
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


bool ImGuiLayer::OnWindowResize(Window& window, int width, int height)
{
    SetDisplaySize(window);
    return false;
}


bool ImGuiLayer::OnWindowScroll(Window& window, double xOffset, double yOffset)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += (float)xOffset;
    io.MouseWheel += (float)yOffset;
    return false;
}


bool ImGuiLayer::OnWindowMonitor(Window& window, int monitorEventType)
{
    // ImGui_ImplGlfw_UpdateMonitors();
    return false;
}


bool ImGuiLayer::OnMouseMove(Window& window, double xPos, double yPos)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2((float)xPos, (float)yPos);
    return false;
}


bool ImGuiLayer::OnMousePress(Window& window, MouseCode button, int action, int mods)
{
    ImGuiIO& io = ImGui::GetIO();
    if (button >= 0)
        io.MouseDown[button] = true;
    return false;
}


bool ImGuiLayer::OnMouseRelease(Window& window, MouseCode button, int action, int mods)
{
    ImGuiIO& io = ImGui::GetIO();
    if (button >= 0)
        io.MouseDown[button] = false;
    return false;
}


bool ImGuiLayer::OnKeyPress(Window& window, KeyCode key, int scancode, int action, int mods)
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[key] = true;

    // Modifiers are not reliable across systems
    io.KeyCtrl = io.KeysDown[KeyCode::LeftControl] || io.KeysDown[KeyCode::RightControl];
    io.KeyShift = io.KeysDown[KeyCode::LeftShift] || io.KeysDown[KeyCode::RightShift];
    io.KeyAlt = io.KeysDown[KeyCode::LeftAlt] || io.KeysDown[KeyCode::RightAlt];
    io.KeySuper = io.KeysDown[KeyCode::LeftSuper] || io.KeysDown[KeyCode::RightSuper];
    return false;
}


bool ImGuiLayer::OnKeyRelease(Window& window, KeyCode key, int scancode, int action, int mods)
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[key] = false;

    // Modifiers are not reliable across systems
    io.KeyCtrl = io.KeysDown[KeyCode::LeftControl] || io.KeysDown[KeyCode::RightControl];
    io.KeyShift = io.KeysDown[KeyCode::LeftShift] || io.KeysDown[KeyCode::RightShift];
    io.KeyAlt = io.KeysDown[KeyCode::LeftAlt] || io.KeysDown[KeyCode::RightAlt];
    io.KeySuper = io.KeysDown[KeyCode::LeftSuper] || io.KeysDown[KeyCode::RightSuper];
    return false;
}


bool ImGuiLayer::OnKeyRepeat(Window& window, KeyCode key, int scancode, int action, int mods)
{
    return false;
}


bool ImGuiLayer::OnCharTyped(Window& window, unsigned int character)
{
    ImGuiIO& io = ImGui::GetIO();
    io.AddInputCharacter(character);
    return false;
}

}
