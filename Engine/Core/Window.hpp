
#pragma once

#include "EngineCommon.h"
#include "Events/EventSource.hpp"
#include "Input/InputSource.hpp"
#include "Input/Cursors.hpp"

namespace Game
{
    class Layer;
    class UILayer;


    struct WindowSpec
    {
        std::string Title;
        int Width;
        int Height;
        Window* ParentWindow = nullptr;
    };


    class Window : public EventSource, public InputSource
    {
    public:
        static Window* Create(const WindowSpec& spec);

        Window(const WindowSpec& spec);
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

        bool VSyncEnabled() { return vsync; }
        virtual void SetVSyncEnabled(bool enabled) = 0;
        void Close();

        int Width() { return width; }
        int Height() { return height; }
        virtual std::pair<int, int> GetFramebufferSize() = 0;
        virtual void SetCursor(Cursor cursor) = 0;

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