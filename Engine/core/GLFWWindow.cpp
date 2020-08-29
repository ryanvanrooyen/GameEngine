
#include "EngineCommon.h"
#include "GLFWWindow.hpp"
#include "Rendering/opengl.hpp"
#include <GLFW/glfw3.h>
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"
#include "Core/logging.h"


namespace Game
{

static void error_callback(int error, const char* description)
{
    ERROR("GLFW Error {}: {}", error, description);
}


GLFWWindow::GLFWWindow(GLFWWindow::Handle* windowHandle, const std::string& name)
    : Window(name) , windowHandle(windowHandle)
{
}


static void InitIMGui(GLFWWindow::Handle* window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGuiIO& io = ImGui::GetIO();
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
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 150";
    ImGui_ImplOpenGL3_Init(glsl_version);
}


unsigned int GLFWWindow::windowCount = 0;


GLFWWindow* GLFWWindow::Create(const std::string& name, GLFWWindow* parentWindow)
{
    // If this is our first Window, initialize Renderer:
    if (windowCount == 0)
    {
        TRACE("Initializing GLFW");

        glfwSetErrorCallback(error_callback);

        if (!glfwInit())
        {
            ERROR("GLFW Initialization Failed.");
            return nullptr;
        }
    }

    TRACE("Creating GLFW Window");
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context:
    Handle* parentWindowHandle = parentWindow ? parentWindow->windowHandle : NULL;
    Handle* windowHandle = glfwCreateWindow(960, 540, name.c_str(), NULL, parentWindowHandle);
    if (!windowHandle)
    {
        ERROR("GLFW Window creation failed.");
        return nullptr;
    }

    TRACE("Making new GLFW Context Current");
    glfwMakeContextCurrent(windowHandle);

    // gl3wInit();

    TRACE("Creating GLFW Context");

    ImGuiContext* imguiContext = nullptr;
    ImFontAtlas* atlas = new ImFontAtlas();
    imguiContext = ImGui::CreateContext(atlas);

    ASSERT(imguiContext, "Failed to create ImGui Context");
    // ImGui::SetCurrentContext(imguiContext);

    if (windowCount == 0)
    {
        TRACE("Loading GLAD to initialize OpenGL context");
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            ERROR("Failed to initialize OpenGL context");
            return nullptr;
        }
        INFO("OpenGL Version {}", glGetString(GL_VERSION));
    }

    // Enable alpha blending:
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    TRACE("Initializing ImGui Context");
    InitIMGui(windowHandle);


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

    GLFWWindow* newWindow = new GLFWWindow(windowHandle, name);
    newWindow->imguiContext = imguiContext;

    glfwSetWindowUserPointer(windowHandle, newWindow);
    glfwSetKeyCallback(windowHandle, Event_KeyPress);

    newWindow->SetVSyncEnabled(true);

    windowCount++;

    return newWindow;
}


void GLFWWindow::MakeCurrent()
{
    glfwMakeContextCurrent(windowHandle);
    // ImGui::SetCurrentContext(imguiContext);
}


void GLFWWindow::PollInput()
{
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    glfwPollEvents();
    // glfwWaitEvents();
}


void GLFWWindow::BeginGUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}


void GLFWWindow::EndGUI()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void GLFWWindow::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}


void GLFWWindow::SwapBuffers()
{
    glfwSwapBuffers(windowHandle);
}


void GLFWWindow::SetVSyncEnabled(bool enabled)
{
    vsync = enabled;
    glfwSwapInterval(vsync ? 1 : 0);
}


void GLFWWindow::Event_KeyPress(Handle* handle, int key, int scancode, int action, int mods)
{
    GLFWWindow* window = (GLFWWindow*)glfwGetWindowUserPointer(handle);
    if (!window) {
        return;
    }

    if (action == GLFW_PRESS) {
        window->DispatchKeyPress(key);
        return;
    }
    if (action == GLFW_RELEASE) {
        window->DispatchKeyRelease(key);
        return;
    }
    if (action == GLFW_REPEAT) {
        window->DispatchKeyRepeat(key);
        return;
    }

    // if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    //     glfwSetWindowShouldClose(window, GLFW_TRUE);
}


GLFWWindow::~GLFWWindow()
{
    glfwDestroyWindow(windowHandle);
    TRACE("Destroying GLFW window {}", name);
    windowCount--;

    if (windowCount == 0)
    {
        TRACE("Shutting down GLFW");

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        TRACE("Terminating GLFW");
        glfwTerminate();
    }
}

}