
#include "Engine.hpp"
#include "../tests/TestMenu.hpp"


int main()
{
    Engine engine;

    Renderer* rendererPtr = engine.Init();
    if (!rendererPtr)
        return 1;

    Renderer& renderer = *rendererPtr;
    test::TestMenu test;

    while (engine.IsRunning())
    {
        engine.CheckInput();

        renderer.Clear();
        renderer.BeginGUI();
        test.OnGuiRender();
        renderer.EndGUI();

        test.OnRender(renderer);

        renderer.SwapBuffers();
    }

    return 0;
}
