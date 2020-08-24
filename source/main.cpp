
#include "core/Engine.hpp"
#include "../tests/TestMenu.hpp"


int main()
{
    Engine* engine = new Engine();

    engine->PushLayer(new test::TestMenu());

    int returnCode = engine->Run();
    delete engine;

    return returnCode;
}
