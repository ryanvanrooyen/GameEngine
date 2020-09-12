
#pragma once

#include "EngineCommon.h"
#include "KeyCodes.hpp"
#include "MouseCodes.hpp"

namespace Game
{
    class InputSource
    {
    public:
        virtual bool IsKeyPressed(KeyCode key) = 0;
        virtual bool IsMousePressed(MouseCode button) = 0;
        virtual std::pair<double, double> GetMousePosition() = 0;
        virtual double GetMouseX() = 0;
        virtual double GetMouseY() = 0;
    };
}