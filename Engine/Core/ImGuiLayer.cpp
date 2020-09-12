
#include "EngineCommon.h"
#include "ImGuiLayer.hpp"
#include "GLFWWindow.hpp"
#include "Rendering/opengl.hpp"
#include <GLFW/glfw3.h>
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"


namespace Game
{

void ImGuiLayer::OnAttach(Window& window)
{
    TRACE("Initializing ImGui");

    GLFWWindow* glfwWindow = dynamic_cast<GLFWWindow*>(&window);
    if (!glfwWindow)
    {
        ERROR("Invalid Window type used with ImGuiLayer.");
        return;
    }

    windowHandle = glfwWindow->GetHandle();

    ImFontAtlas* atlas = new ImFontAtlas();
    context = ImGui::CreateContext(atlas);
    ASSERT(context, "Failed to create ImGui Context");

    // ImGui::SetCurrentContext(context);

    ImGuiIO& io = ImGui::GetIO();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(1.3f);
    io.Fonts->AddFontDefault();
    io.FontGlobalScale = 1.3f;
    io.Fonts->Build();

    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(windowHandle, false);
    const char* glsl_version = "#version 150";
    ImGui_ImplOpenGL3_Init(glsl_version);


    // Example on how to init 2 windows:

    // GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
    // glfwMakeContextCurrent(window);
    // gl3wInit();
    // ImGuiContext* ctx1 = ImGui::GetCurrentContext();

    // // Setup ImGui binding
    // ImGui_ImplGlfwGL3_Init(window, true);

    // GLFWwindow* window2 = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
    // glfwMakeContextCurrent(window2);
    // gl3wInit();

    // ImGuiContext* ctx2 = ImGui::CreateContext();
    // ImGui::SetCurrentContext(ctx2);

    // // Setup ImGui binding
    // ImGui_ImplGlfwGL3_Init(window2, true);
}


void ImGuiLayer::OnDetach(Window& window)
{
    TRACE("Shutting down ImGui");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void ImGuiLayer::BeginGUI(Window& window)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    io.DeltaTime = 0.f;
    io.DisplaySize = ImVec2(window.Width(), window.Height());
    // Temporarily test out the demo window:
    bool show = true;
    ImGui::ShowDemoWindow(&show);
}


void ImGuiLayer::EndGUI(Window& window)
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


bool ImGuiLayer::OnWindowResize(Window& window, int width, int height)
{
    return false;
}


bool ImGuiLayer::OnWindowScroll(Window& window, double xOffset, double yOffset)
{
    ImGui_ImplGlfw_ScrollCallback(windowHandle, xOffset, yOffset);
    return true;
}


bool ImGuiLayer::OnWindowMonitor(Window& window, int monitorEventType)
{
    ImGui_ImplGlfw_MonitorCallback(nullptr, monitorEventType);
    return false;
}


bool ImGuiLayer::OnMouseMove(Window& window, double xPos, double yPos)
{
    return false;
}


bool ImGuiLayer::OnMousePress(Window& window, MouseCode button, int action, int mods)
{
    ImGui_ImplGlfw_MouseButtonCallback(windowHandle, (int)button, action, mods);
    return true;
}


bool ImGuiLayer::OnMouseRelease(Window& window, MouseCode button, int action, int mods)
{
    ImGui_ImplGlfw_MouseButtonCallback(windowHandle, (int)button, action, mods);
    return true;
}


bool ImGuiLayer::OnKeyPress(Window& window, KeyCode key, int scancode, int action, int mods)
{
    ImGui_ImplGlfw_KeyCallback(windowHandle, (int)key, scancode, action, mods);
    return true;
}


bool ImGuiLayer::OnKeyRelease(Window& window, KeyCode key, int scancode, int action, int mods)
{
    ImGui_ImplGlfw_KeyCallback(windowHandle, (int)key, scancode, action, mods);
    return true;
}


bool ImGuiLayer::OnKeyRepeat(Window& window, KeyCode key, int scancode, int action, int mods)
{
    ImGui_ImplGlfw_KeyCallback(windowHandle, (int)key, scancode, action, mods);
    return true;
}


bool ImGuiLayer::OnCharTyped(Window& window, unsigned int character)
{
    ImGui_ImplGlfw_CharCallback(windowHandle, character);
    return true;
}

}

