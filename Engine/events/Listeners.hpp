
#pragma once

namespace Game
{
    class Window;

    class EventListener
    {
    public:
        virtual bool OnKeyPress(Window& window, int key) { return false; }
        virtual bool OnKeyRelease(Window& window, int key) { return false; }
        virtual bool OnKeyRepeat(Window& window, int key) { return false; }

    };

}