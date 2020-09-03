
#include "EngineCommon.h"
#include "Engine.hpp"
#include "Window.hpp"
#include "Core/logging.h"

namespace Game
{

Engine::Engine()
{
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
            // mainWindow->MakeCurrent();
            mainWindow->PollInput();
            mainWindow->Clear();
            mainWindow->Update(0.f);
            mainWindow->SwapBuffers();

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


bool Engine::OnKeyPress(Window& window, KeyCode key)
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