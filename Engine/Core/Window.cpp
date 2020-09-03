
#include "EngineCommon.h"
#include "Window.hpp"
#include "logging.h"
#include "Layer.hpp"
#include "Events/Listeners.hpp"
#include "GLFWWindow.hpp"
#include "Rendering/Renderer.hpp"


namespace Game
{

Window* Window::Create(const std::string& name, Window* parent)
{
    // TODO: This should use a preprocessor flag to decide what type of window to create:
    GLFWWindow* glfwParent = dynamic_cast<GLFWWindow*>(parent);
    return GLFWWindow::Create(name, glfwParent);
}


Window::Window(const std::string& name) : name(name)
{
}


void Window::Update(float deltaTime)
{
    // PollInput();
    // Clear();

    for (Layer* layer : layers)
        layer->OnUpdate(deltaTime);

    BeginGUI();
    for (Layer* layer : layers)
        layer->OnGUIRender(*this);
    EndGUI();

    // SwapBuffers();
}


void Window::PushLayer(Layer* layer)
{
    if (layer)
    {
        TRACE("Attaching layer: {}", layer->LayerName());
        layers.emplace(layers.begin() + layerInsertIndex, layer);
		layerInsertIndex++;
        layer->OnAttach(*this);

        if (EventListener* listener = dynamic_cast<EventListener*>(layer))
            PushListener(listener);
    }
}


void Window::PushOverlay(Layer* overlay)
{
    if (overlay)
    {
        TRACE("Attaching overlay: {}", overlay->LayerName());
        layers.emplace_back(overlay);
        overlay->OnAttach(*this);

        if (EventListener* listener = dynamic_cast<EventListener*>(overlay))
            PushListener(listener);
    }
}


void Window::PopLayer(Layer* layer)
{
    if (layer)
    {
        auto it = std::find(layers.begin(), layers.begin() + layerInsertIndex, layer);
		if (it != layers.begin() + layerInsertIndex)
		{
            TRACE("Detaching layer: {}", layer->LayerName());
			layer->OnDetach(*this);
			layers.erase(it);
			layerInsertIndex--;

            if (EventListener* listener = dynamic_cast<EventListener*>(layer))
                PopListener(listener);
		}
    }
}


void Window::PopOverlay(Layer* overlay)
{
    if (overlay)
    {
        auto it = std::find(layers.begin() + layerInsertIndex, layers.end(), overlay);
        if (it != layers.end())
        {
            TRACE("Detaching overlay: {}", overlay->LayerName());
            overlay->OnDetach(*this);
            layers.erase(it);

            if (EventListener* listener = dynamic_cast<EventListener*>(overlay))
                PopListener(listener);
        }
    }
}



Window::~Window()
{
    for (Layer* layer : layers)
    {
        TRACE("Detaching layer: {}", layer->LayerName());
        layer->OnDetach(*this);
        TRACE("Deleting layer: {}", layer->LayerName());
        delete layer;
    }

    TRACE("Deleting window: {}", name);
}

}