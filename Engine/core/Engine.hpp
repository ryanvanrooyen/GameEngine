
#pragma once

#include "../Events/Listeners.hpp"


namespace Game
{
    class Window;
    class Layer;

    class Engine : public EventListener
    {
    public:
        Engine();

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopOverlay(Layer* overlay);

        int Run();
        bool IsRunning() { return isRunning; }
        void Quit();

        // Events:
        bool OnKeyPress(Window& window, int key) override;

        virtual ~Engine();

    private:
        Window* mainWindow;
        bool isRunning = false;
    };

}