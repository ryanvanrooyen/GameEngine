
#pragma once

#include "EngineCommon.h"
#include "KeyCodes.hpp"
#include "MouseCodes.hpp"

namespace Game
{
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode key);
        static bool IsMousePressed(MouseCode button);
        static std::pair<double, double> GetMousePosition();
        static double GetMouseX();
        static double GetMouseY();
    };
}