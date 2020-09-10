
#pragma once

#include "Core/Layer.hpp"

namespace Game
{
    class Window;
    class TestMenu;

    class Test : public Layer
    {
    public:
        void OnGUIRender(Window& window, float deltaTime) override;
        virtual void OnTestGUI(Window& window, float deltaTime) {}
        virtual ~Test() { TRACE("Deleting Test"); }

    protected:
        void BackToMenu(Window& window);

    private:
        friend class TestMenu;
        TestMenu* menu;
    };

}