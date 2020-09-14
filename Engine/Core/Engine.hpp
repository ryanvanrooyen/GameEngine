
#pragma once

#include "EngineCommon.h"
#include "Events/Listeners.hpp"

namespace Game
{
    class Window;
    class Layer;

    class Engine : public EventListener
    {
    public:
        Engine();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        int Run();
        float DeltaTime() { return deltaTime; }
        bool IsRunning() { return isRunning; }
        void Quit();

        // Events:
        bool OnWindowClose(Window& window) override;
        bool OnKeyPress(Window& window, KeyCode key, int scancode, int action, int mods) override;

        virtual ~Engine();

        Window* ActiveWindow() { return mainWindow; }
        static Engine* Instance() { return instance; }

    private:
        static Engine* instance;
        Window* mainWindow;
        bool isRunning = false;
        float deltaTime = 0.f;
    };

}