

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

        GLFWWindow(Handle* windowHandle, const std::string& name);
        virtual ~GLFWWindow();

        virtual void MakeCurrent() override;
        virtual void PollInput() override;
        virtual void Clear() override;
        virtual void SwapBuffers() override;

        virtual void BeginGUI() override;
        virtual void EndGUI() override;

        static GLFWWindow* Create(const std::string& name, GLFWWindow* parentWindow = nullptr);

    private:
        static unsigned int windowCount;
        Handle* windowHandle = nullptr;
        ImGuiContext* imguiContext;

        static void Event_KeyPress(Handle* handle, int key, int scancode, int action, int mods);
    };

}