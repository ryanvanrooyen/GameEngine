
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
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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


// static void DrawImGUIWindow()
// {
//     static bool show_demo_window = true;
//     static bool show_another_window = false;
//     ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
//     static float f = 0.0f;
//     static int counter = 0;

//     ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

//     ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//     ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//     ImGui::Checkbox("Another Window", &show_another_window);

//     ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//     ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

//     if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//         counter++;

//     ImGui::SameLine();
//     ImGui::Text("counter = %d", counter);

//     ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//     ImGui::End();
// }


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
    // glfwSwapInterval(1);  // V-Sync

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        ERROR("Failed to initialize OpenGL context");
        return -1;
    }

    INFO("OpenGL Version %s", glGetString(GL_VERSION));

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 150";
    ImGui_ImplOpenGL3_Init(glsl_version);

    float positions[] = {
        0.f,   0.f, 0.f, 0.f,
        100.f, 0.f, 1.f, 0.f,
        100.f, 100.f, 1.f, 1.f,
        0.f,   100.f, 0.f, 1.f,
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
    glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0));
    glm::vec3 translation(200, 200, 0);

    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    shader.Compile();
    shader.Bind();


    Texture texture("resources/logo3.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    Renderer renderer;

    float redColor = 0.0f;
    float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        // glfwWaitEvents();

        renderer.Clear();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // shader.Bind();
        // shader.SetUniform4f("u_Color", redColor, 0.3f, 0.8f, 1.f);

        glm::mat4 model = glm::translate(glm::mat4(1.f), translation);
        glm::mat4 mvp = proj * view * model;
        shader.SetUniformMat4f("u_MVP", mvp);

        ImGui::Begin("Test");
        ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        renderer.Draw(va, indexBuffer, shader);

        if (redColor > 1.f || redColor < 0.f)
            increment = -increment;

        redColor += increment;

        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

