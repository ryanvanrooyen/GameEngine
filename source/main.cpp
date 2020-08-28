
#include "core/logging.h"
#include "core/Engine.hpp"
#include "../tests/TestMenu.hpp"
#include "../tests/TestColorChangingSquare.hpp"
#include "../tests/TestSingleImage.hpp"


int main()
{
    ENABLE_LOGGING();
    SET_LOG_FORMAT("%^%@: %l: %v%$");

    Game::Engine* engine = new Game::Engine();

    engine->PushLayer(new Game::Test::TestMenu());
    // engine->PushLayer(new Game::Test::TestColorChangingSquare());
    // engine->secondaryWindow->PushLayer(new Game::Test::TestSingleImage());
    // engine->secondaryWindow->PushLayer(new Game::Test::TestColorChangingSquare());

    int returnCode = engine->Run();
    delete engine;

    return returnCode;
}
