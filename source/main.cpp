
#include "core/Engine.hpp"
#include "../tests/TestMenu.hpp"


int main()
{
    Game::Engine* engine = new Game::Engine();

    engine->PushLayer(new Game::Test::TestMenu());

    int returnCode = engine->Run();
    delete engine;

    return returnCode;
}
