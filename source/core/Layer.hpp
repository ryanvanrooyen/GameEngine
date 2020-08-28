
#pragma once


namespace Game
{
    class Window;

    class Layer
    {
    public:
        virtual const char* LayerName() const = 0;
        virtual void OnAttach(Window& window) {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnGUIRender(Window& window) {}
        virtual void OnDetach(Window& window) {}
        virtual ~Layer() = default;
    };

}