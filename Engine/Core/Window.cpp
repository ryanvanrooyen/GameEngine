
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
    // Make sure to remove any pending layers before checking input:
    if (hasLayersToRemove)
    {
        RemovePendingLayers();
        hasLayersToRemove = false;
    }

    PollInput();
    Clear();

    for (const std::shared_ptr<Layer>& layer : layers)
    {
        if (layer->Enabled())
            layer->OnUpdate(*this, deltaTime);
    }

    BeginGUI();
    for (const std::shared_ptr<Layer>& layer : layers)
    {
        if (layer->Enabled())
            layer->OnGUIRender(*this, deltaTime);
    }
    EndGUI();

    SwapBuffers();
}


void Window::Close()
{
    DispatchWindowClose(*this);
}


void Window::PushLayer(const std::shared_ptr<Layer>& layer)
{
    if (layer)
    {
        TRACE("Attaching layer: {}", layer->LayerName());
        layers.emplace(layers.begin() + layerInsertIndex, layer);
		layerInsertIndex++;
        layer->OnAttach(*this);
        PushListener(layer.get());
    }
}


void Window::PushOverlay(const std::shared_ptr<Layer>& overlay)
{
    if (overlay)
    {
        TRACE("Attaching overlay: {}", overlay->LayerName());
        layers.emplace_back(overlay);
        overlay->OnAttach(*this);
        PushListener(overlay.get());
    }
}


// void Window::PopLayer(Layer* layer)
// {
//     if (!layer)
//         return;
//     auto it = std::find_if(layers.begin(), layers.begin() + layerInsertIndex, [layer](std::shared_ptr<Layer> l) {return layer == l.get();});
//     if (it != layers.begin() + layerInsertIndex)
//     {
//         auto it2 = std::find(layersToRemove.begin(), layersToRemove.end(), *it);
//         bool isNotAlreadyPendingToBeRemoveed = it2 == layersToRemove.end();
//         if (isNotAlreadyPendingToBeRemoveed)
//         {
//             layersToRemove.push_back(*it);
//             hasLayersToRemove = true;
//         }
//     }
// }


void Window::PopLayer(const std::shared_ptr<Layer>& layer)
{
    if (!layer)
        return;

    auto it = std::find(layers.begin(), layers.begin() + layerInsertIndex, layer);
    if (it != layers.begin() + layerInsertIndex)
    {
        auto it2 = std::find(layersToRemove.begin(), layersToRemove.end(), *it);
        bool isNotAlreadyPendingToBeRemoveed = it2 == layersToRemove.end();
        if (isNotAlreadyPendingToBeRemoveed)
        {
            layersToRemove.push_back(*it);
            hasLayersToRemove = true;
        }
    }
}


void Window::PopOverlay(const std::shared_ptr<Layer>& overlay)
{
    if (!overlay)
        return;

    auto it = std::find(layers.begin() + layerInsertIndex, layers.end(), overlay);
    if (it != layers.end())
    {
        auto it2 = std::find(overlaysToRemove.begin(), overlaysToRemove.end(), *it);
        bool isNotAlreadyPendingToBeRemoveed = it2 == overlaysToRemove.end();
        if (isNotAlreadyPendingToBeRemoveed)
        {
            overlaysToRemove.push_back(*it);
            hasLayersToRemove = true;
        }
    }
}


void Window::RemovePendingLayers()
{
    for (std::shared_ptr<Layer>& layer : overlaysToRemove)
    {
        auto it = std::find(layers.begin() + layerInsertIndex, layers.begin(), layer);
		if (it != layers.end())
		{
            TRACE("Detaching layer: {}", layer->LayerName());
			layer->OnDetach(*this);
			layers.erase(it);
            PopListener(layer.get());
		}
    }

    for (std::shared_ptr<Layer>& layer : layersToRemove)
    {
        auto it = std::find(layers.begin(), layers.begin() + layerInsertIndex, layer);
		if (it != layers.begin() + layerInsertIndex)
		{
            TRACE("Detaching layer: {}", layer->LayerName());
			layer->OnDetach(*this);
			layers.erase(it);
			layerInsertIndex--;
            PopListener(layer.get());
		}
    }

    overlaysToRemove.clear();
    layersToRemove.clear();
}


Window::~Window()
{
    for (std::shared_ptr<Layer>& layer : layers)
    {
        TRACE("Detaching layer: {}", layer->LayerName());
        layer->OnDetach(*this);
    }

    TRACE("Deleting window: {}", name);
}

}