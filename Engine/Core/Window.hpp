
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

        void PushLayer(const std::shared_ptr<Layer>& layer);
        void PushOverlay(const std::shared_ptr<Layer>& overlay);
        void PopLayer(const std::shared_ptr<Layer>& layer);
        void PopOverlay(const std::shared_ptr<Layer>& overlay);
        void SetUILayer(const std::shared_ptr<UILayer>& uiLayer);

        static Window* Create(const std::string& name, Window* parent = nullptr);

        bool VSyncEnabled() { return vsync; }
        virtual void SetVSyncEnabled(bool enabled) = 0;
        void Close();

        int Width() { return width; }
        int Height() { return height; }

    protected:
        std::string name;
        bool vsync = false;
        int width, height;
        void DestroyLayers();

    private:
        std::shared_ptr<UILayer> uiLayer;
        unsigned int layerInsertIndex = 0;
        std::vector<std::shared_ptr<Layer>> layers;
        std::vector<std::shared_ptr<Layer>> layersToRemove;
        std::vector<std::shared_ptr<Layer>> overlaysToRemove;
        bool hasLayersToRemove = false;
        void RemovePendingLayers();
    };

}