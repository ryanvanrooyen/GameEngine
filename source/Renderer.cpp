
#include "Renderer.hpp"
#include <iostream>

void GLClearErrors()
{
    while (glGetError());
}

bool GLCheckErrors(const char * function, const char* file, int line)
{
    bool noErrors = true;
    while (GLenum error = glGetError())
    {
        WARNF("[OpenGL Error %#08x] %s(%d): %s\n", error, file, line, function);
        noErrors = false;
    }
    return noErrors;
}
