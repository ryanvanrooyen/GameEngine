
#pragma once

struct GLFWwindow;

class Engine
{
private:
    GLFWwindow* window = nullptr;

public:
    ~Engine();

    bool Init();
    bool IsRunning();
    void CheckInput();

    void ClearScreen();
    void SwapBuffers();
};
