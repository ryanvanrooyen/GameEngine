
#include "EngineCommon.h"
#include "Core/Engine.hpp"
#include "TestMenu.hpp"
#include "TestColorChangingSquare.hpp"
#include "TestSingleImage.hpp"


int main()
{
    ENABLE_LOGGING();
    SET_LOG_FORMAT("%^%@: %l: %v%$");

    Game::Engine* engine = new Game::Engine();

    engine->PushLayer(new Game::TestMenu());
    // engine->secondaryWindow->PushLayer(new Game::TestSingleImage());
    // engine->secondaryWindow->PushLayer(new Game::TestColorChangingSquare());

    int returnCode = engine->Run();
    delete engine;

    return returnCode;
}
