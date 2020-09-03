
#include "EngineCommon.h"
#include "EventSource.hpp"
#include "Listeners.hpp"
#include "Core/Window.hpp"
#include "Core/logging.h"

namespace Game
{

void EventSource::PushListener(EventListener* listener)
{
    if (listener)
    {
        // Push listeners at front of list so listeners on top get first dibs at handling events:
        eventListeners.insert(eventListeners.begin(), listener);
    }
}


void EventSource::PopListener(EventListener* listener)
{
    if (listener)
    {
        auto it = std::find(eventListeners.begin(), eventListeners.end(), listener);
        if (it != eventListeners.end())
        {
            eventListeners.erase(it);
        }
    }
}


#define DISPATCH(Event, listeners, ...)\
    for (EventListener* listener : listeners)\
    {\
        if (listener->Event(__VA_ARGS__))\
            break;\
    }


void EventSource::DispatchWindowClose(Window& window)
{
    TRACE("Dispatching Event: {} WindowClose", window.Name());
    DISPATCH(OnWindowClose, eventListeners, window);
}

void EventSource::DispatchWindowResize(Window& window, int width, int height)
{
    // TRACE("Dispatching Event: {} WindowResize ({}, {})", window.Name(), width, height);
    DISPATCH(OnWindowResize, eventListeners, window, width, height);
}


void EventSource::DispatchWindowScroll(Window& window, double xOffset, double yOffset)
{
    // TRACE("Dispatching Event: {} WindowScroll ({}, {})", window.Name(), xOffset, yOffset);
    DISPATCH(OnWindowScroll, eventListeners, window, xOffset, yOffset);
}


void EventSource::DispatchMouseMove(Window& window, double xPos, double yPos)
{
    // TRACE("Dispatching Event: {} WindowMove ({}, {})", window.Name(), xPos, yPos);
    DISPATCH(OnMouseMove, eventListeners, window, xPos, yPos);
}


void EventSource::DispatchMousePress(Window& window, MouseCode button)
{
    TRACE("Dispatching Event: {} MousePress {}", window.Name(), button);
    DISPATCH(OnMousePress, eventListeners, window, button);
}


void EventSource::DispatchMouseRelease(Window& window, MouseCode button)
{
    TRACE("Dispatching Event: {} MouseRelease {}", window.Name(), button);
    DISPATCH(OnMouseRelease, eventListeners, window, button);
}


void EventSource::DispatchKeyPress(Window& window, KeyCode key)
{
    TRACE("Dispatching Event: {} KeyPress {}", window.Name(), key);
    DISPATCH(OnKeyPress, eventListeners, window, key);
}


void EventSource::DispatchKeyRelease(Window& window, KeyCode key)
{
    TRACE("Dispatching Event: {} KeyRelease {}", window.Name(), key);
    DISPATCH(OnKeyRelease, eventListeners, window, key);
}


void EventSource::DispatchKeyRepeat(Window& window, KeyCode key)
{
    TRACE("Dispatching Event: {} KeyRepeat {}", window.Name(), key);
    DISPATCH(OnKeyRepeat, eventListeners, window, key);
}

}