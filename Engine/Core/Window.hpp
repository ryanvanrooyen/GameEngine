
#pragma once

#include "EngineCommon.h"
#include "Events/EventSource.hpp"
#include "Input/InputSource.hpp"

namespace Game
{
    class Layer;
    class UILayer;

    class Window : public EventSource, public InputSource
    {
    public:
        Window(const std::string& name, int width, int height);
        virtual ~Window();

        std::string Name() { return name; }

        virtual void PollInput() = 0;

        void Update(float deltaTime);
        virtual void MakeCurrent() = 0;
        virtual void Clear() = 0;
        virtual void SwapBuffers() = 0;

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);
        void SetUILayer(UILayer* uiLayer);

        static Window* Create(const std::string& name, Window* parent = nullptr);

        bool VSyncEnabled() { return vsync; }
        virtual void SetVSyncEnabled(bool enabled) = 0;
        void Close();

        int Width() { return width; }
        int Height() { return height; }
        virtual std::pair<int, int> GetFramebufferSize() = 0;

    protected:
        std::string name;
        bool vsync = false;
        int width, height;
        void DestroyLayers();

    private:
        UILayer* uiLayer;
        unsigned int layerInsertIndex = 0;
        std::vector<Layer*> layers;
    };

}