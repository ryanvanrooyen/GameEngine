
#include "EngineCommon.h"
#include "Window.hpp"
#include "Layer.hpp"
#include "Events/Listeners.hpp"
#include "GLFWWindow.hpp"
#include "Rendering/Renderer.hpp"


namespace Game
{

Window* Window::Create(const std::string& name, Window* parent)
{
    // TODO: This should use a preprocessor flag to decide what type of window to create:
    return GLFWWindow::Create(name, (GLFWWindow*)parent);
}


Window::Window(const std::string& name, int width, int height)
    : name(name), width(width), height(height)
{
}


void Window::Update(float deltaTime)
{
    Clear();

    for (Layer* layer : layers)
    {
        if (layer->Enabled())
            layer->OnUpdate(*this, deltaTime);
    }

    uiLayer->BeginGUI(*this, deltaTime);
    for (Layer* layer : layers)
    {
        if (layer->Enabled())
            layer->OnGUIRender(*this, deltaTime);
    }
    uiLayer->EndGUI(*this, deltaTime);

    SwapBuffers();
}


void Window::Close()
{
    DispatchWindowClose(*this);
}


void Window::PushLayer(Layer* layer)
{
    if (layer)
    {
        TRACE("Attaching layer: {}", layer->LayerName());
        layers.emplace(layers.begin() + layerInsertIndex, layer);
		layerInsertIndex++;
        layer->OnAttach(*this);
        PushListener(layer);
    }
}


void Window::PushOverlay(Layer* overlay)
{
    if (overlay)
    {
        TRACE("Attaching overlay: {}", overlay->LayerName());
        layers.emplace_back(overlay);
        overlay->OnAttach(*this);
        PushListener(overlay);
    }
}


void Window::SetUILayer(UILayer* uiLayer)
{
    // Remove the old ui layer if there is one:
    if (this->uiLayer)
        PopOverlay(this->uiLayer);

    this->uiLayer = uiLayer;
    PushOverlay(uiLayer);
}


void Window::PopLayer(Layer* layer)
{
    if (!layer)
        return;

    auto it = std::find(layers.begin(), layers.begin() + layerInsertIndex, layer);
    if (it != layers.begin() + layerInsertIndex)
    {
        TRACE("Removing layer: {}", layer->LayerName());
        layer->OnDetach(*this);
        layers.erase(it);
        layerInsertIndex--;
        PopListener(layer);
    }
}


void Window::PopOverlay(Layer* overlay)
{
    if (!overlay)
        return;

    auto it = std::find(layers.begin() + layerInsertIndex, layers.end(), overlay);
    if (it != layers.end())
    {
        TRACE("Removing layer: {}", overlay->LayerName());
        overlay->OnDetach(*this);
        layers.erase(it);
        PopListener(overlay);
    }
}


void Window::DestroyLayers()
{
    for (Layer* layer : layers)
    {
        TRACE("Destroying layer: {}", layer->LayerName());
        layer->OnDetach(*this);
        delete layer;
    }
    layers.clear();
}


Window::~Window()
{
    DestroyLayers();
}

}