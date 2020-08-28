
#include "../source/core/Layer.hpp"
#include "../source/core/Window.hpp"
#include "../source/events/Listeners.hpp"

namespace Game::Test
{

    class TestMenu : public Layer, public EventListener
    {
    public:
        const char* LayerName() const override { return "TestMenu"; }
        void OnAttach(Window& window) override;
        void OnGUIRender(Window& window) override;
        void OnDetach(Window& window) override;
        bool OnKeyPress(Window& window, int key) override;
        ~TestMenu();

    private:
        Layer* test = nullptr;
        Window* parentWindow = nullptr;

        void SetChildTest(Layer* newTest);
    };

}