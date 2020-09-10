
#include "EngineCommon.h"
#include "EventSource.hpp"

namespace Game
{

// Push listeners at front of list so listeners on top get first dibs at handling events:
#define DEFINE_PUSH(Listener, listeners)\
    void EventSource::PushListener(Listener* listener)\
    {\
        if (listener)\
            listeners.insert(listeners.begin(), listener);\
    }


#define DEFINE_POP(Listener, listeners)\
    void EventSource::PopListener(Listener* listener)\
    {\
        if (listener)\
        {\
            auto it = std::find(listeners.begin(), listeners.end(), listener);\
            if (it != listeners.end())\
                listeners.erase(it);\
        }\
    }


#define DISPATCH(Event, listeners, ...)\
    for (auto& listener : listeners)\
    {\
        if (listener->Event(__VA_ARGS__))\
            return true;\
    }\
    return false;


DEFINE_PUSH(WindowListener, windowListeners);
DEFINE_PUSH(MouseListener, mouseListeners);
DEFINE_PUSH(KeyboardListener, keyboardListeners);
DEFINE_POP(WindowListener, windowListeners);
DEFINE_POP(MouseListener, mouseListeners);
DEFINE_POP(KeyboardListener, keyboardListeners);


bool EventSource::DispatchWindowClose(Window& window) { DISPATCH(OnWindowClose, windowListeners, window); }
bool EventSource::DispatchWindowResize(Window& window, int width, int height) { DISPATCH(OnWindowResize, windowListeners, window, width, height); }
bool EventSource::DispatchWindowScroll(Window& window, double xOffset, double yOffset) { DISPATCH(OnWindowScroll, windowListeners, window, xOffset, yOffset); }
bool EventSource::DispatchMouseMove(Window& window, double xPos, double yPos) { DISPATCH(OnMouseMove, mouseListeners, window, xPos, yPos); }
bool EventSource::DispatchMousePress(Window& window, MouseCode button) { DISPATCH(OnMousePress, mouseListeners, window, button); }
bool EventSource::DispatchMouseRelease(Window& window, MouseCode button) { DISPATCH(OnMouseRelease, mouseListeners, window, button); }
bool EventSource::DispatchKeyPress(Window& window, KeyCode key) { DISPATCH(OnKeyPress, keyboardListeners, window, key); }
bool EventSource::DispatchKeyRelease(Window& window, KeyCode key) { DISPATCH(OnKeyRelease, keyboardListeners, window, key); }
bool EventSource::DispatchKeyRepeat(Window& window, KeyCode key) { DISPATCH(OnKeyRepeat, keyboardListeners, window, key); }

}