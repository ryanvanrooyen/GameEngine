
#include "EngineCommon.h"
#include "Engine.hpp"
#include "Window.hpp"
#include "ImGuiLayer.hpp"

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;


namespace Game
{


Engine* Engine::instance;


Engine::Engine()
{
    instance = this;
    mainWindow = Window::Create("Main");
    if (mainWindow) {
        mainWindow->PushListener(this);
        mainWindow->SetUILayer(new ImGuiLayer());
    }
}


int Engine::Run()
{
    try
    {
        if (!mainWindow)
            return 1;

        high_resolution_clock::time_point previousFrameTime = high_resolution_clock::now();
        isRunning = true;

        while (isRunning)
        {
            high_resolution_clock::time_point currentTime = high_resolution_clock::now();
            deltaTime = (float)duration_cast<duration<double>>(currentTime - previousFrameTime).count();
            previousFrameTime = currentTime;

            mainWindow->PollInput();
            mainWindow->Update(deltaTime);

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