
#include "EngineCommon.h"
#include "ImGuiLayer.hpp"
#include "Window.hpp"
#include "Input/Cursors.hpp"
#include "examples/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>


namespace Game
{


static std::unordered_map<int, Cursor> CursorMappings = {
    {ImGuiMouseCursor_Arrow, Cursor::Arrow },
    {ImGuiMouseCursor_TextInput, Cursor::IBeam },
    {ImGuiMouseCursor_Hand, Cursor::Hand },
    {ImGuiMouseCursor_ResizeNS, Cursor::ResizeNS },
    {ImGuiMouseCursor_ResizeEW, Cursor::ResizeEW },
    {ImGuiMouseCursor_ResizeNESW, Cursor::ResizeNESW },
    {ImGuiMouseCursor_ResizeNWSE, Cursor::ResizeNWSE },
    {ImGuiMouseCursor_ResizeAll, Cursor::ResizeAll },
    {ImGuiMouseCursor_NotAllowed, Cursor::NotAllowed },
    {ImGuiMouseCursor_None, Cursor::None }};


// Helper stuct we store in the void* RenderUserData field of each ImGuiViewport to retrieve our backend data.
struct ImGuiViewportDataGlfw
{
    Window* Window = nullptr;
    bool    WindowOwned = false;
    int     IgnoreWindowPosEventFrame = -1;
    int     IgnoreWindowSizeEventFrame = -1;
    ~ImGuiViewportDataGlfw() { ASSERT(Window == nullptr, "ImGui Viewport Window not cleaned up!"); }
};


static void ImGui_ImplGlfw_CreateWindow(ImGuiViewport* viewport)
{
    ImGuiViewportDataGlfw* data = IM_NEW(ImGuiViewportDataGlfw)();
    viewport->PlatformUserData = data;

    WindowSpec newWindowSpec = {};

    // GLFW 3.2 unfortunately always set focus on glfwCreateWindow() if GLFW_VISIBLE is set, regardless of GLFW_FOCUSED
    // With GLFW 3.3, the hint GLFW_FOCUS_ON_SHOW fixes this problem
    glfwWindowHint(GLFW_VISIBLE, false);
    glfwWindowHint(GLFW_FOCUSED, false);
#if GLFW_HAS_FOCUS_ON_SHOW
     glfwWindowHint(GLFW_FOCUS_ON_SHOW, false);
 #endif
    glfwWindowHint(GLFW_DECORATED, (viewport->Flags & ImGuiViewportFlags_NoDecoration) ? false : true);
#if GLFW_HAS_WINDOW_TOPMOST
    glfwWindowHint(GLFW_FLOATING, (viewport->Flags & ImGuiViewportFlags_TopMost) ? true : false);
#endif
    // GLFWwindow* share_window = (g_ClientApi == GlfwClientApi_OpenGL) ? g_Window : NULL;
    // glfwCreateWindow((int)viewport->Size.x, (int)viewport->Size.y, "No Title Yet", NULL, share_window);

    data->Window = Window::Create(newWindowSpec);
    data->WindowOwned = true;
    viewport->PlatformHandle = (void*)data->Window;

    // glfwSetWindowPos(data->Window, (int)viewport->Pos.x, (int)viewport->Pos.y);
    data->Window->MakeCurrent();
    data->Window->SetVSyncEnabled(false);
}


static void InitPlatformInterface(Window& window)
{
    // Register platform interface (will be coupled with a renderer interface)
    ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
    platform_io.Platform_CreateWindow = ImGui_ImplGlfw_CreateWindow;
    // platform_io.Platform_DestroyWindow = ImGui_ImplGlfw_DestroyWindow;
    // platform_io.Platform_ShowWindow = ImGui_ImplGlfw_ShowWindow;
    // platform_io.Platform_SetWindowPos = ImGui_ImplGlfw_SetWindowPos;
    // platform_io.Platform_GetWindowPos = ImGui_ImplGlfw_GetWindowPos;
    // platform_io.Platform_SetWindowSize = ImGui_ImplGlfw_SetWindowSize;
    // platform_io.Platform_GetWindowSize = ImGui_ImplGlfw_GetWindowSize;
    // platform_io.Platform_SetWindowFocus = ImGui_ImplGlfw_SetWindowFocus;
    // platform_io.Platform_GetWindowFocus = ImGui_ImplGlfw_GetWindowFocus;
    // platform_io.Platform_GetWindowMinimized = ImGui_ImplGlfw_GetWindowMinimized;
    // platform_io.Platform_SetWindowTitle = ImGui_ImplGlfw_SetWindowTitle;
    // platform_io.Platform_RenderWindow = ImGui_ImplGlfw_RenderWindow;
    // platform_io.Platform_SwapBuffers = ImGui_ImplGlfw_SwapBuffers;

// #if GLFW_HAS_WINDOW_ALPHA
//     platform_io.Platform_SetWindowAlpha = ImGui_ImplGlfw_SetWindowAlpha;
// #endif
// #if GLFW_HAS_VULKAN
//     platform_io.Platform_CreateVkSurface = ImGui_ImplGlfw_CreateVkSurface;
// #endif
// #if HAS_WIN32_IME
//     platform_io.Platform_SetImeInputPos = ImGui_ImplWin32_SetImeInputPos;
// #endif

    // Register main window handle (which is owned by the main application, not by us)
    // This is mostly for simplicity and consistency, so that our code (e.g. mouse handling etc.) can use same logic for main and secondary viewports.
    ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGuiViewportDataGlfw* data = IM_NEW(ImGuiViewportDataGlfw)();
    data->Window = &window;
    data->WindowOwned = false;
    main_viewport->PlatformUserData = data;
    main_viewport->PlatformHandle = (void*)&window;
}


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
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
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

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        InitPlatformInterface(window);

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

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        window.MakeCurrent();
    }
}


bool ImGuiLayer::OnWindowResize(Window& window)
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

    if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)
        return false;

    window.SetCursor(CursorMappings[ImGui::GetMouseCursor()]);
    return false;
}


bool ImGuiLayer::OnMousePress(Window& window, MouseCode button)
{
    ImGuiIO& io = ImGui::GetIO();
    if (button >= 0)
        io.MouseDown[button] = true;
    return false;
}


bool ImGuiLayer::OnMouseRelease(Window& window, MouseCode button)
{
    ImGuiIO& io = ImGui::GetIO();
    if (button >= 0)
        io.MouseDown[button] = false;
    return false;
}


bool ImGuiLayer::OnKeyPress(Window& window, KeyCode key)
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


bool ImGuiLayer::OnKeyRelease(Window& window, KeyCode key)
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


bool ImGuiLayer::OnKeyRepeat(Window& window, KeyCode key)
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
