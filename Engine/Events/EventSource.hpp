
#pragma once

#include "EngineCommon.h"
#include "Core/Input.hpp"

namespace Game
{
    class Window;
    class EventListener;

    class EventSource
    {
    public:
        void PushListener(EventListener* listener);
        void PopListener(EventListener* listener);

    protected:
        void DispatchWindowClose(Window& window);
        void DispatchWindowResize(Window& window, int width, int height);
        void DispatchWindowScroll(Window& window, double xOffset, double yOffset);

        void DispatchMouseMove(Window& window, double xPos, double yPos);
        void DispatchMousePress(Window& window, MouseCode button);
        void DispatchMouseRelease(Window& window, MouseCode button);

        void DispatchKeyPress(Window& window, KeyCode key);
        void DispatchKeyRelease(Window& window, KeyCode key);
        void DispatchKeyRepeat(Window& window, KeyCode key);

    private:
        std::vector<EventListener*> eventListeners;
    };
}