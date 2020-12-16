
#include "EngineCommon.h"
#include "Engine.hpp"
#include "GLFWWindow.hpp"
#include "Rendering/opengl.hpp"
#include "Rendering/Renderer.hpp"
#include <GLFW/glfw3.h>


namespace Game
{

static void error_callback(int error, const char* description)
{
    ERROR("GLFW Error {}: {}", error, description);
}


GLFWWindow::GLFWWindow(GLFWWindow::Handle* windowHandle, const WindowSpec& spec)
    : Window(spec), windowHandle(windowHandle)
{
}


unsigned int GLFWWindow::windowCount = 0;


GLFWWindow* GLFWWindow::Create(const WindowSpec& spec)
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
    GLFWWindow* parentWindow = spec.ParentWindow ? (GLFWWindow*)spec.ParentWindow : nullptr;
    Handle* parentWindowHandle = parentWindow ? parentWindow->windowHandle : nullptr;

    Handle* windowHandle = glfwCreateWindow(spec.Width, spec.Height, spec.Title.c_str(), nullptr, parentWindowHandle);
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

    GLFWWindow* newWindow = new GLFWWindow(windowHandle, spec);

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

    // Example on how to init 2 windows:
    // GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
    // glfwMakeContextCurrent(window);
    // gl3wInit();
    // ImGuiContext* ctx1 = ImGui::GetCurrentContext();
    // ImGui_ImplGlfwGL3_Init(window, true);

    // GLFWwindow* window2 = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
    // glfwMakeContextCurrent(window2);
    // gl3wInit();
    // ImGuiContext* ctx2 = ImGui::CreateContext();
    // ImGui::SetCurrentContext(ctx2);
    // ImGui_ImplGlfwGL3_Init(window2, true);

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
        window->Update(Engine::Instance()->DeltaTime());
    }
}


void GLFWWindow::Event_WindowResize(Handle* handle, int width, int height)
{
    GLFWWindow* window = (GLFWWindow*)glfwGetWindowUserPointer(handle);
    if (window) {
        window->width = width;
        window->height = height;
        window->DispatchWindowResize(*window);
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
        window->DispatchMousePress(*window, (MouseCode)button);
    else if (action == GLFW_RELEASE)
        window->DispatchMouseRelease(*window, (MouseCode)button);
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
        window->DispatchKeyPress(*window, (KeyCode)key);
    else if (action == GLFW_RELEASE)
        window->DispatchKeyRelease(*window, (KeyCode)key);
    else if (action == GLFW_REPEAT)
        window->DispatchKeyRepeat(*window, (KeyCode)key);
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


std::pair<int, int> GLFWWindow::GetFramebufferSize()
{
    int width, height;
    glfwGetFramebufferSize(windowHandle, &width, &height);
    return { width, height };
}


void GLFWWindow::SetCursor(Cursor cursor)
{
    if (cursor == currentCursor)
        return;

    TRACE("Setting cursor: {}", cursor);
    if (cursor == Cursor::None)
    {
        glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        return;
    }

    GLFWcursor* glfwCursor = glfwCreateStandardCursor(cursor);
    if (!glfwCursor)
    {
        WARN("Unable to create cursor: {}", cursor);
        cursor = Cursor::Arrow;
        glfwCursor = glfwCreateStandardCursor(cursor);
    }
    glfwSetCursor(windowHandle, glfwCursor);

    if (currentCursor == Cursor::None)
        glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    currentCursor = cursor;
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