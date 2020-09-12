
#pragma once

#include "EngineCommon.h"
#include "Listeners.hpp"

namespace Game
{
    class Window;

    class EventSource
    {
    public:
        virtual ~EventSource() = default;

        void PushListener(WindowListener* listener);
        void PushListener(MouseListener* listener);
        void PushListener(KeyboardListener* listener);
        void PushListener(EventListener* listener)
        {
            PushListener((WindowListener*)listener);
            PushListener((MouseListener*)listener);
            PushListener((KeyboardListener*)listener);
        }

        void PopListener(WindowListener* listener);
        void PopListener(MouseListener* listener);
        void PopListener(KeyboardListener* listener);
        void PopListener(EventListener* listener)
        {
            PopListener((WindowListener*)listener);
            PopListener((MouseListener*)listener);
            PopListener((KeyboardListener*)listener);
        }

    protected:
        bool DispatchWindowClose(Window& window);
        bool DispatchWindowResize(Window& window, int width, int height);
        bool DispatchWindowScroll(Window& window, double xOffset, double yOffset);
        bool DispatchWindowMonitor(Window& window, int monitorEventType);

        bool DispatchMouseMove(Window& window, double xPos, double yPos);
        bool DispatchMousePress(Window& window, MouseCode button, int action, int mods);
        bool DispatchMouseRelease(Window& window, MouseCode button, int action, int mods);

        bool DispatchKeyPress(Window& window, KeyCode key, int scancode, int action, int mods);
        bool DispatchKeyRelease(Window& window, KeyCode key, int scancode, int action, int mods);
        bool DispatchKeyRepeat(Window& window, KeyCode key, int scancode, int action, int mods);
        bool DispatchCharTyped(Window& window, unsigned int character);

    private:
        std::vector<WindowListener*> windowListeners;
        std::vector<MouseListener*> mouseListeners;
        std::vector<KeyboardListener*> keyboardListeners;
    };
}