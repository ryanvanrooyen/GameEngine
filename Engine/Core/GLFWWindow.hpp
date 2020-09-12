

#pragma once

#include "Window.hpp"

struct GLFWwindow;

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

        virtual void SetVSyncEnabled(bool enabled) override;

        static GLFWWindow* Create(const std::string& name, GLFWWindow* parentWindow = nullptr);

        virtual bool IsKeyPressed(KeyCode key) override;
        virtual bool IsMousePressed(MouseCode button) override;
        virtual std::pair<double, double> GetMousePosition() override;
        virtual double GetMouseX() override;
        virtual double GetMouseY() override;

        Handle* GetHandle() { return windowHandle; }

    private:
        static unsigned int windowCount;
        Handle* windowHandle = nullptr;

        static void Event_WindowClose(Handle* handle);
        static void Event_WindowRefresh(Handle* handle);
        static void Event_WindowResize(Handle* handle, int width, int height);
        static void Event_WindowScroll(Handle* handle, double xOffset, double yOffset);
        static void Event_MousePress(Handle* handle, int button, int action, int mods);
        static void Event_MouseMove(Handle* handle, double xPos, double yPos);
        static void Event_KeyPress(Handle* handle, int key, int scancode, int action, int mods);
        static void Event_CharTyped(Handle* handle, unsigned int character);
    };
}