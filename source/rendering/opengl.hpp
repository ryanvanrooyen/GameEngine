
#include <glad/glad.h>
#include "../logging.h"

#define GLCall(x) GLClearErrors(); x; ASSERT(GLCheckErrors(#x, __FILE__, __LINE__), "OpenGL Call Failed")

void GLClearErrors();
bool GLCheckErrors(const char * function, const char* file, int line);
