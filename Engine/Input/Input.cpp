
#include "Input.hpp"
#include "Core/Engine.hpp"
#include "Core/Window.hpp"

namespace Game
{

bool Input::IsKeyPressed(KeyCode key)
{
    return Engine::Instance()->ActiveWindow()->IsKeyPressed(key);
}


bool Input::IsMousePressed(MouseCode button)
{
    return Engine::Instance()->ActiveWindow()->IsMousePressed(button);
}


std::pair<double, double> Input::GetMousePosition()
{
    return Engine::Instance()->ActiveWindow()->GetMousePosition();
}


double Input::GetMouseX()
{
    return Engine::Instance()->ActiveWindow()->GetMouseX();
}


double Input::GetMouseY()
{
    return Engine::Instance()->ActiveWindow()->GetMouseY();
}

}