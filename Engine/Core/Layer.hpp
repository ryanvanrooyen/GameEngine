
#pragma once

#include "Events/EventSource.hpp"
#include "Events/Listeners.hpp"

namespace Game
{
    class Window;

    class Layer : public EventSource, public EventListener
    {
    public:
        bool Enabled() { return enabled; }
        void SetEnabled(bool enabled) { this->enabled = enabled; }

        virtual const char* LayerName() const = 0;
        virtual void OnAttach(Window& window) {}
        virtual void OnUpdate(Window& window, float deltaTime) {}
        virtual void OnGUIRender(Window& window, float deltaTime) {}
        virtual void OnDetach(Window& window) {}
        virtual ~Layer() = default;

        // Propagate events:
        bool OnWindowClose(Window& window) override { return enabled && DispatchWindowClose(window); }
        bool OnWindowResize(Window& window, int width, int height) override { return enabled && DispatchWindowResize(window, width, height); }
        bool OnWindowScroll(Window& window, double xOffset, double yOffset) override { return enabled && DispatchWindowScroll(window, xOffset, yOffset); }

        bool OnMouseMove(Window& window, double xPos, double yPos) override { return enabled && DispatchMouseMove(window, xPos, yPos); }
        bool OnMousePress(Window& window, MouseCode button) override { return enabled && DispatchMousePress(window, button); }
        bool OnMouseRelease(Window& window, MouseCode button) override { return enabled && DispatchMouseRelease(window, button); }

        bool OnKeyPress(Window& window, KeyCode key) override { return enabled && DispatchKeyPress(window, key); }
        bool OnKeyRelease(Window& window, KeyCode key) override { return enabled && DispatchKeyRelease(window, key); }
        bool OnKeyRepeat(Window& window, KeyCode key) override { return enabled && DispatchKeyRepeat(window, key); }

    private:
        bool enabled = true;
    };

}