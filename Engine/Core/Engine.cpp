
#include "EngineCommon.h"
#include "Engine.hpp"
#include "Window.hpp"

namespace Game
{


Engine* Engine::instance;


Engine::Engine()
{
    instance = this;
    mainWindow = Window::Create("Main");
    if (mainWindow) {
        mainWindow->PushListener(this);
    }
}


int Engine::Run()
{
    try
    {
        if (!mainWindow)
            return 1;

        isRunning = true;
        while (isRunning)
        {
            mainWindow->PollInput();
            mainWindow->Update(0.f);

            // secondaryWindow->MakeCurrent();
            // secondaryWindow->PollInput();
            // secondaryWindow->Update(0.f);
            // secondaryWindow->SwapBuffers();
            // secondaryWindow->Clear();
        }
    }
    catch (const std::exception& exc)
    {
        ERROR("Exception occured: {}", exc.what());
        return 2;
    }
    catch (...)
    {
        return 3;
    }

    return 0;
}


void Engine::Quit()
{
    isRunning = false;
}


bool Engine::OnWindowClose(Window& window)
{
    Quit();
    return true;
}


bool Engine::OnKeyPress(Window& window, KeyCode key, int scancode, int action, int mods)
{
    if (key == KeyCode::Escape) {
        Quit();
        return true;
    }
    return false;
}


void Engine::PushLayer(Layer* layer)
{
    if (mainWindow)
        mainWindow->PushLayer(layer);
}


void Engine::PopLayer(Layer* layer)
{
    if (mainWindow)
        mainWindow->PopLayer(layer);
}


void Engine::PushOverlay(Layer* overlay)
{
    if (mainWindow)
        mainWindow->PushOverlay(overlay);
}


void Engine::PopOverlay(Layer* overlay)
{
    if (mainWindow)
        mainWindow->PopOverlay(overlay);
}


Engine::~Engine()
{
    if (mainWindow)
    {
        delete mainWindow;
    }
}

}