
#pragma once

#include "EngineCommon.h"
#include "Core/Layer.hpp"

namespace Game
{
    class Test : public Layer
    {
    public:
        virtual const char* LayerName() const override { return "Test"; }
        virtual ~Test() { TRACE("Deleting Test"); }
    };
}