
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

        void PushLayer(const std::shared_ptr<Layer>& layer);
        void PushOverlay(const std::shared_ptr<Layer>& overlay);
        void PopLayer(const std::shared_ptr<Layer>& layer);
        void PopOverlay(const std::shared_ptr<Layer>& overlay);

        int Run();
        bool IsRunning() { return isRunning; }
        void Quit();

        // Events:
        bool OnWindowClose(Window& window) override;
        bool OnKeyPress(Window& window, KeyCode key) override;

        virtual ~Engine();

    private:
        Window* mainWindow;
        bool isRunning = false;
    };

}