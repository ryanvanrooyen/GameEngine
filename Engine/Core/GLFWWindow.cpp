
#include "EngineCommon.h"
#include "GLFWWindow.hpp"
#include "ImGuiLayer.hpp"
#include "Rendering/opengl.hpp"
#include "Rendering/Renderer.hpp"
#include <GLFW/glfw3.h>


namespace Game
{

static void error_callback(int error, const char* description)
{
    ERROR("GLFW Error {}: {}", error, description);
}


GLFWWindow::GLFWWindow(GLFWWindow::Handle* windowHandle, const std::string& name, int width, int height)
    : Window(name, width, height) , windowHandle(windowHandle)
{
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

    int width = 1920;
    int height = 1080;

    Handle* windowHandle = glfwCreateWindow(width, height, name.c_str(), NULL, parentWindowHandle);
    if (!windowHandle)
    {
        ERROR("GLFW Window creation failed.");
        return nullptr;
    }

    TRACE("Making new GLFW Context Current");
    glfwMakeContextCurrent(windowHandle);

    TRACE("Creating GLFW Context");

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


    Renderer::EnableAlphaBlending();

    GLFWWindow* newWindow = new GLFWWindow(windowHandle, name, width, height);

    newWindow->SetUILayer(new ImGuiLayer());

    glfwSetWindowUserPointer(windowHandle, newWindow);
    glfwSetWindowCloseCallback(windowHandle, Event_WindowClose);
    glfwSetWindowRefreshCallback(windowHandle, Event_WindowRefresh);
    glfwSetWindowSizeCallback(windowHandle, Event_WindowResize);
    glfwSetScrollCallback(windowHandle, Event_WindowScroll);
    glfwSetMouseButtonCallback(windowHandle, Event_MousePress);
    glfwSetCursorPosCallback(windowHandle, Event_MouseMove);
    glfwSetKeyCallback(windowHandle, Event_KeyPress);
    glfwSetCharCallback(windowHandle, Event_CharTyped);

    // glfwSetMonitorCallback([newWindow] (GLFWmonitor* monitor, int monitorEventType) {
    //     newWindow->DispatchWindowMonitor(*newWindow, monitorEventType);
    // });

    newWindow->SetVSyncEnabled(true);

    windowCount++;

    return newWindow;
}


void GLFWWindow::MakeCurrent()
{
    glfwMakeContextCurrent(windowHandle);
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


void GLFWWindow::Clear()
{
    Renderer::Clear();
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


void GLFWWindow::Event_WindowClose(Handle* handle)
{
    GLFWWindow* window = (GLFWWindow*)glfwGetWindowUserPointer(handle);
    if (window) {
        window->DispatchWindowClose(*window);
    }
}


void GLFWWindow::Event_WindowRefresh(Handle* handle)
{
    GLFWWindow* window = (GLFWWindow*)glfwGetWindowUserPointer(handle);
    if (window) {
        float deltaTime = 0.f;  // TODO: Get current delta time
        window->Update(deltaTime);
    }
}


void GLFWWindow::Event_WindowResize(Handle* handle, int width, int height)
{
    GLFWWindow* window = (GLFWWindow*)glfwGetWindowUserPointer(handle);
    if (window) {
        int previousWidth = window->width;
        int previousHeight = window->height;
        window->width = width;
        window->height = height;
        window->DispatchWindowResize(*window, previousWidth, previousHeight);
    }
}


void GLFWWindow::Event_WindowScroll(Handle* handle, double xOffset, double yOffset)
{
    GLFWWindow* window = (GLFWWindow*)glfwGetWindowUserPointer(handle);
    if (window) {
        window->DispatchWindowScroll(*window, xOffset, yOffset);
    }
}


void GLFWWindow::Event_MousePress(Handle* handle, int button, int action, int mods)
{
    GLFWWindow* window = (GLFWWindow*)glfwGetWindowUserPointer(handle);
    if (!window) {
        return;
    }

    if (action == GLFW_PRESS)
        window->DispatchMousePress(*window, (MouseCode)button, action, mods);
    else if (action == GLFW_RELEASE)
        window->DispatchMouseRelease(*window, (MouseCode)button, action, mods);
}


void GLFWWindow::Event_MouseMove(Handle* handle, double xPos, double yPos)
{
    GLFWWindow* window = (GLFWWindow*)glfwGetWindowUserPointer(handle);
    if (window) {
        window->DispatchMouseMove(*window, xPos, yPos);
    }
}


void GLFWWindow::Event_KeyPress(Handle* handle, int key, int scancode, int action, int mods)
{
    GLFWWindow* window = (GLFWWindow*)glfwGetWindowUserPointer(handle);
    if (!window) {
        return;
    }

    if (action == GLFW_PRESS)
        window->DispatchKeyPress(*window, (KeyCode)key, scancode, action, mods);
    else if (action == GLFW_RELEASE)
        window->DispatchKeyRelease(*window, (KeyCode)key, scancode, action, mods);
    else if (action == GLFW_REPEAT)
        window->DispatchKeyRepeat(*window, (KeyCode)key, scancode, action, mods);
}


void GLFWWindow::Event_CharTyped(Handle* handle, unsigned int character)
{
    GLFWWindow* window = (GLFWWindow*)glfwGetWindowUserPointer(handle);
    if (window) {
        window->DispatchCharTyped(*window, character);
    }
}


bool GLFWWindow::IsKeyPressed(KeyCode key)
{
    return glfwGetKey(windowHandle, key) == GLFW_PRESS;
}


bool GLFWWindow::IsMousePressed(MouseCode button)
{
    return glfwGetMouseButton(windowHandle, button) == GLFW_PRESS;
}


std::pair<double, double> GLFWWindow::GetMousePosition()
{
    double xPos, yPos;
    glfwGetCursorPos(windowHandle, &xPos, &yPos);
    return { xPos, yPos };
}


double GLFWWindow::GetMouseX()
{
    double xPos, yPos;
    glfwGetCursorPos(windowHandle, &xPos, &yPos);
    return xPos;
}


double GLFWWindow::GetMouseY()
{
    double xPos, yPos;
    glfwGetCursorPos(windowHandle, &xPos, &yPos);
    return yPos;
}


GLFWWindow::~GLFWWindow()
{
    TRACE("Destroying GLFW window {}", name);
    DestroyLayers();

    glfwDestroyWindow(windowHandle);
    windowCount--;

    if (windowCount == 0)
    {
        TRACE("Terminating GLFW");
        glfwTerminate();
    }
}

}