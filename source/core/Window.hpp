
#pragma once

#include <vector>
#include <string>

namespace Game
{
    class Layer;
    class EventListener;

    class Window
    {
    public:
        Window(const std::string& name);
        virtual ~Window();

        std::string Name() { return name; }

        void Update(float deltaTime);
        virtual void MakeCurrent() = 0;
        virtual void PollInput() = 0;
        virtual void Clear() = 0;
        virtual void SwapBuffers() = 0;

        virtual void BeginGUI() = 0;
        virtual void EndGUI() = 0;

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopOverlay(Layer* overlay);

        void PushListener(EventListener* listener);
        void PopListener(EventListener* listener);

        static Window* Create(const std::string& name, Window* parent = nullptr);

    protected:
        std::string name;

        void DispatchKeyPress(int key);
        void DispatchKeyRelease(int key);
        void DispatchKeyRepeat(int key);

    private:
        unsigned int layerInsertIndex = 0;
        std::vector<Layer*> layers;
        std::vector<EventListener*> eventListeners;
    };

}