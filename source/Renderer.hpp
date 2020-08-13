
#pragma once

#include <glad/glad.h>
#include "logging.hpp"

#define GLCall(x) GLClearErrors(); x; ASSERT(GLCheckErrors(#x, __FILE__, __LINE__))

void GLClearErrors();
bool GLCheckErrors(const char * function, const char* file, int line);
