
#include "opengl.hpp"

namespace Game
{

void GLClearErrors()
{
    while (glGetError());
}

bool GLCheckErrors(const char * function, const char* file, int line)
{
    bool noErrors = true;
    while (GLenum error = glGetError())
    {
        ERROR_DETAILS(file, line, "OpenGL Error %#06x: %s", error, function);
        noErrors = false;
    }
    return noErrors;
}

}