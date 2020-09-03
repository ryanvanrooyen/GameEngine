
#pragma once

#include "EngineCommon.h"
#include "Events/EventSource.hpp"

namespace Game
{
    class Layer;

    class Window : public EventSource
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

        static Window* Create(const std::string& name, Window* parent = nullptr);

        bool VSyncEnabled() { return vsync; }
        virtual void SetVSyncEnabled(bool enabled) = 0;

    protected:
        bool vsync = false;
        std::string name;

    private:
        unsigned int layerInsertIndex = 0;
        std::vector<Layer*> layers;
    };

}