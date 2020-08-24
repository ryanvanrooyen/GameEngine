
#include <exception>
#include "Engine.hpp"
#include "../rendering/opengl.hpp"
#include "../rendering/Renderer.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "../core/logging.h"


int Engine::Run()
{
    try
    {
        if (!Init())
            return 1;

        while (IsRunning())
        {
            CheckInput();
            ClearScreen();

            for (Layer* layer : layers)
                layer->OnUpdate(0.f);

            Renderer::BeginGUI();
            for (Layer* layer : layers)
                layer->OnGuiRender();
            Renderer::EndGUI();

            SwapBuffers();
        }
    }
    catch (const std::exception& exc)
    {
        ERROR("Exception occured: %s", exc.what());
        return 2;
    }
    catch (...)
    {
        return 3;
    }

    return 0;
}


void Engine::PushLayer(Layer* layer)
{
    if (layer)
        layers.push_back(layer);
}


Engine::~Engine()
{
    for (Layer* layer : layers)
        delete layer;

    if (window)
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}


static void error_callback(int error, const char* description)
{
    ERROR("Error: %s", description);
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}


static void InitIMGui(GLFWwindow* window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    io.FontGlobalScale = 1.3f;
    style.ScaleAllSizes(1.3f);
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


bool Engine::Init()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context:
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);

    if (!window)
        return false;

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    // glfwSwapInterval(1);  // V-Sync

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        ERROR("Failed to initialize OpenGL context");
        return false;
    }

    INFO("OpenGL Version %s", glGetString(GL_VERSION));
    // Enable alpha blending:
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    InitIMGui(window);
    return true;
}


bool Engine::IsRunning()
{
    return window && !glfwWindowShouldClose(window);
}


void Engine::CheckInput()
{
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    glfwPollEvents();
    // glfwWaitEvents();
}


void Engine::ClearScreen()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}


void Engine::SwapBuffers()
{
    glfwSwapBuffers(window);
}
