
#pragma once

#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include "Core/logging.h"

// Clear any previous errors, call the GL function x, then assert any errors:
#define GLCall(x) \
    while (glGetError());\
    x;\
    while (GLenum error = glGetError())\
    {\
        ERROR("OpenGL Error {:x}: {}", error, #x);\
    }\
