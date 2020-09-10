
#include "EngineCommon.h"
#include "Core/Layer.hpp"
#include "Core/Window.hpp"

namespace Game
{
    class Test;

    class TestMenu : public Layer
    {
    public:
        const char* LayerName() const override { return "TestMenu"; }
        void OnGUIRender(Window& window, float deltaTime) override;
        bool OnKeyPress(Window& window, KeyCode key) override;

        void SetChildTest(Window& window, const std::shared_ptr<Test>& newTest);

    private:
        std::shared_ptr<Test> test = nullptr;
        void OnGUISelectTest(Window& window);
    };
}