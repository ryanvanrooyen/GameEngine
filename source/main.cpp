
#include "Engine.hpp"
#include "rendering/Renderer.hpp"
#include "../tests/TestMenu.hpp"


int main()
{
    Engine engine;

    if (!engine.Init())
        return 1;

    test::TestMenu test;

    while (engine.IsRunning())
    {
        engine.CheckInput();
        engine.ClearScreen();

        Renderer::BeginGUI();
        test.OnGuiRender();
        Renderer::EndGUI();

        test.OnRender();

        engine.SwapBuffers();
    }

    return 0;
}
