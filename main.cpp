
#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <signal.h>
#include "source/logging.hpp"
#include "source/Renderer.hpp"
#include "source/Shader.hpp"
#include "source/VertexBuffer.hpp"
#include "source/VertexBufferLayout.hpp"
#include "source/IndexBuffer.hpp"
#include "source/VertexArray.hpp"

using std::string;


static void error_callback(int error, const char* description)
{
    ERROR("Error: %s", description);
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}


int main()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    INFO("OpenGL Version %s", glGetString(GL_VERSION));

    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
    };

    VertexBuffer vertexBuffer(positions, 4 * 2 * sizeof(float));

    VertexBufferLayout vertexLayout;
    vertexLayout.Push<float>(2);

    VertexArray va;
    va.AddBuffer(vertexBuffer, vertexLayout);

    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0,
    };

    IndexBuffer indexBuffer(indicies, 6);

    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    shader.Compile();
    shader.Bind();

    float redColor = 0.0f;
    float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();
        // glfwWaitEvents();

        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        // GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
        shader.SetUniform4f("u_Color", redColor, 0.3f, 0.8f, 1.f);
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        if (redColor > 1.f || redColor < 0.f)
            increment = -increment;

        redColor += increment;

        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
