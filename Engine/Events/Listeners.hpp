
#pragma once

#include "Core/Input.hpp"

namespace Game
{
    class Window;

    class EventListener
    {
    public:
        virtual bool OnWindowClose(Window& window) { return false; }
        virtual bool OnWindowResize(Window& window, int width, int height) { return false; }
        virtual bool OnWindowScroll(Window& window, double xOffset, double yOffset) { return false; }

        virtual bool OnMouseMove(Window& window, double xPos, double yPos) { return false; }
        virtual bool OnMousePress(Window& window, MouseCode button) { return false; }
        virtual bool OnMouseRelease(Window& window, MouseCode button) { return false; }

        virtual bool OnKeyPress(Window& window, KeyCode key) { return false; }
        virtual bool OnKeyRelease(Window& window, KeyCode key) { return false; }
        virtual bool OnKeyRepeat(Window& window, KeyCode key) { return false; }
    };

}