
#include "EngineCommon.h"
#include "Core/Layer.hpp"


namespace Game
{
    class Test;
    class Window;

    class TestMenu : public Layer
    {
    public:
        const char* LayerName() const override { return "TestMenu"; }
        void OnUpdate(Window& window, float deltaTime) override;
        void OnGUIRender(Window& window, float deltaTime) override;
        bool OnKeyPress(Window& window, KeyCode key, int scancode, int action, int mods) override;

    private:
        Test* test = nullptr;
        void OnGUISelectTest(Window& window);
        bool DestroyTest(Window& window);
    };
}