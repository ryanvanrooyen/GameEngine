
#pragma once

#include "Input/KeyCodes.hpp"
#include "Input/MouseCodes.hpp"

namespace Game
{
    class Window;

    class WindowListener
    {
    public:
        virtual bool OnWindowClose(Window& window) { return false; }
        virtual bool OnWindowResize(Window& window, int width, int height) { return false; }
        virtual bool OnWindowScroll(Window& window, double xOffset, double yOffset) { return false; }
        virtual bool OnWindowMonitor(Window& window, int monitorEventType) { return false; }
    };

    class MouseListener
    {
    public:
        virtual bool OnMouseMove(Window& window, double xPos, double yPos) { return false; }
        virtual bool OnMousePress(Window& window, MouseCode button, int action, int mods) { return false; }
        virtual bool OnMouseRelease(Window& window, MouseCode button, int action, int mods) { return false; }
    };

    class KeyboardListener
    {
    public:
        virtual bool OnKeyPress(Window& window, KeyCode key, int scancode, int action, int mods) { return false; }
        virtual bool OnKeyRelease(Window& window, KeyCode key, int scancode, int action, int mods) { return false; }
        virtual bool OnKeyRepeat(Window& window, KeyCode key, int scancode, int action, int mods) { return false; }
        virtual bool OnCharTyped(Window& window, unsigned int character) { return false; }
    };

    class EventListener :
        public WindowListener,
        public MouseListener,
        public KeyboardListener {};
}