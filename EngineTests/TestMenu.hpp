
#include "Core/Layer.hpp"
#include "Core/Window.hpp"
#include "Events/Listeners.hpp"

namespace Game::Test
{

    class TestMenu : public Layer, public EventListener
    {
    public:
        const char* LayerName() const override { return "TestMenu"; }
        void OnAttach(Window& window) override;
        void OnGUIRender(Window& window) override;
        void OnDetach(Window& window) override;
        bool OnKeyPress(Window& window, KeyCode key) override;
        ~TestMenu();

    private:
        Layer* test = nullptr;
        Window* parentWindow = nullptr;

        void SetChildTest(Layer* newTest);
    };

}