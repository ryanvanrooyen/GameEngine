
#pragma once

#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../core/logging.h"

#define GLCall(x) GLClearErrors(); x; ASSERT(GLCheckErrors(#x, __FILE__, __LINE__), "OpenGL Call Failed")

void GLClearErrors();
bool GLCheckErrors(const char * function, const char* file, int line);
