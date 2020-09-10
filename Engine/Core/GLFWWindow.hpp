

#pragma once

#include "Window.hpp"

struct GLFWwindow;
struct ImGuiContext;

namespace Game
{
    class GLFWWindow : public Window
    {
    public:
        using Handle = GLFWwindow;

        GLFWWindow(Handle* windowHandle, const std::string& name, int width, int height);
        virtual ~GLFWWindow();

        virtual void MakeCurrent() override;
        virtual void PollInput() override;
        virtual void Clear() override;
        virtual void SwapBuffers() override;

        virtual void BeginGUI() override;
        virtual void EndGUI() override;

        virtual void SetVSyncEnabled(bool enabled) override;

        static GLFWWindow* Create(const std::string& name, GLFWWindow* parentWindow = nullptr);

    private:
        static unsigned int windowCount;
        Handle* windowHandle = nullptr;
        ImGuiContext* imguiContext;

        static void Event_WindowClose(Handle* handle);
        static void Event_WindowResize(Handle* handle, int width, int height);
        static void Event_WindowScroll(Handle* handle, double xOffset, double yOffset);
        static void Event_MousePress(Handle* handle, int button, int action, int mods);
        static void Event_MouseMove(Handle* handle, double xPos, double yPos);
        static void Event_KeyPress(Handle* handle, int key, int scancode, int action, int mods);
    };
}