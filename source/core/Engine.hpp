
#pragma once

#include <vector>
#include "Layer.hpp"

struct GLFWwindow;

namespace Game
{

class Engine
{
public:
    int Run();
    void PushLayer(Layer* layer);
    ~Engine();

private:
    bool Init();
    bool IsRunning();
    void CheckInput();

    void ClearScreen();
    void SwapBuffers();

    GLFWwindow* window = nullptr;
    std::vector<Layer*> layers;
};

}