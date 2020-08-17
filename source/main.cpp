
#define GL_SILENCE_DEPRECATION
#include "rendering/opengl.hpp"
#include <string>
#include <signal.h>
#include "logging.h"
#include "rendering/Renderer.hpp"
#include "rendering/Shader.hpp"
#include "rendering/Texture.hpp"
#include "rendering/VertexBuffer.hpp"
#include "rendering/VertexBufferLayout.hpp"
#include "rendering/IndexBuffer.hpp"
#include "rendering/VertexArray.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);

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
        ERROR("Failed to initialize OpenGL context");
        return -1;
    }

    INFO("OpenGL Version %s", glGetString(GL_VERSION));

    float positions[] = {
        100.f, 100.f, 0.f, 0.f,
        200.f, 100.f, 1.f, 0.f,
        200.f, 200.f, 1.f, 1.f,
        100.f, 200.f, 0.f, 1.f,
    };

    VertexBuffer vertexBuffer(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout vertexLayout;
    vertexLayout.Push<float>(2); // 2D Position
    vertexLayout.Push<float>(2); // 2D Texture Position

    // Enable alpha blending:
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray va;
    va.AddBuffer(vertexBuffer, vertexLayout);

    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0,
    };

    IndexBuffer indexBuffer(indicies, 6);

    glm::mat4 proj = glm::ortho(0.f, 960.f, 0.f, 540.f, -1.f, 1.f);
    glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(100, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(200, 200, 0));

    glm::mat4 mvp = proj * view * model;

    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    shader.Compile();
    shader.Bind();

    shader.SetUniformMat4f("u_MVP", mvp);

    Texture texture("resources/logo3.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    Renderer renderer;

    float redColor = 0.0f;
    float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();
        // glfwWaitEvents();

        renderer.Clear();

        // shader.Bind();
        // shader.SetUniform4f("u_Color", redColor, 0.3f, 0.8f, 1.f);

        renderer.Draw(va, indexBuffer, shader);

        if (redColor > 1.f || redColor < 0.f)
            increment = -increment;

        redColor += increment;

        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
