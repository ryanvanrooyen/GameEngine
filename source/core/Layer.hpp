
#pragma once

namespace Game
{

class Layer
{
public:
    virtual const char* LayerName() const = 0;
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnGuiRender() {}
    virtual ~Layer() = default;
};

}