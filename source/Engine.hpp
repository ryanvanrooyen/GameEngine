
#pragma once

struct GLFWwindow;
class Renderer;

class Engine
{
private:
    GLFWwindow* window = nullptr;
    Renderer* renderer = nullptr;

public:
    ~Engine();

    Renderer* Init();
    bool IsRunning();
    void CheckInput();
};
