
#include <glad/glad.h>

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <signal.h>

using std::string;

#define WARN(msg) fprintf(stderr, msg)
#define WARNF(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)

#ifdef DEBUG
    #define ASSERT(x) if (!(x)) __asm__("int $3")
#else
    #define ASSERT(x)
#endif

#define GLCall(x) GLClearErrors(); x; ASSERT(GLCheckErrors(#x, __FILE__, __LINE__))

static void GLClearErrors()
{
    while (glGetError());
}

static bool GLCheckErrors(const char * function, const char* file, int line)
{
    bool noErrors = true;
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error "
            << std::showbase << std::hex << error << "]: "
            << function << " " << file << ":"
            << std::dec << line << std::endl;
        noErrors = false;
    }
    return noErrors;
}

struct ShaderSource
{
    string VertexShader;
    string FragmentShader;
};

static ShaderSource ParseShader(const string& filepath)
{
    std::ifstream file(filepath);

    std::stringstream shaders[2];
    unsigned int shaderIndex = 0;

    string line;
    while (getline(file, line))
    {
        if (line.find("#shader") != string::npos)
        {
            if (line.find("vertex") != string::npos)
                shaderIndex = 0;
            else if (line.find("fragment") != string::npos)
                shaderIndex = 1;
        }
        else
        {
            shaders[shaderIndex] << line << std::endl;
        }
    }

    return { shaders[0].str(), shaders[1].str() };
}

static string readFile(const string& filepath) {
  std::ostringstream buffer;
  std::ifstream inputFile (filepath);
  buffer << inputFile.rdbuf();
  return buffer.str();
}

static unsigned int compileShaderFile(unsigned int type, const string& filepath)
{
    string fileContent = readFile(filepath);
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = fileContent.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    // TODO: Handle shader compilation errors:
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << filepath << ":" << std::endl << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

static unsigned int compileShader(unsigned int type, const string& shader)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = shader.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    // TODO: Handle shader compilation errors:
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile "
            << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << " shader: " << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

static void useShader(unsigned int programId, unsigned int type, const string& filepath)
{
    unsigned int shaderId = compileShaderFile(type, filepath);
    if (shaderId == 0)
        return;

    GLCall(glAttachShader(programId, shaderId));
    // GLCall(glLinkProgram(program));
    // GLCall(glValidateProgram(program));
    // GLCall(glDeleteShader(shaderId));
}

static unsigned int createShader(const string& vertextShader, const string& fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertextShader);
    if (vs == 0)
        return 0;
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    if (fs == 0)
        return 0;

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

static void SetUniformVector4(unsigned int programId, const char* variableName, float v1, float v2, float v3, float v4)
{
    GLCall(unsigned int uniformLocation = glGetUniformLocation(programId, variableName));
    if (uniformLocation == -1)
        WARNF("Uniform \"%s\" not found\n", variableName);
    GLCall(glUniform4f(uniformLocation, v1, v2, v3, v4));
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
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

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
    };

    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0,
    };

    unsigned int buffer;
    GLCall(glGenBuffers(1, &buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW));

    GLuint vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    // ShaderSource shaders = ParseShader("shaders/shaders.glsl");
    // std::cout << "Loaded Vertex Shader:" << shaders.VertexShader << std::endl;
    // std::cout << "Loaded Fragment Shader:" << shaders.FragmentShader << std::endl;
    // std::cout << "Loaded Test:" << readFile("blah.txt") << std::endl;
    // unsigned int program = createShader(shaders.VertexShader, shaders.FragmentShader);

    GLCall(unsigned int program = glCreateProgram());
    useShader(program, GL_VERTEX_SHADER, "shaders/vertexShader.glsl");
    useShader(program, GL_FRAGMENT_SHADER, "shaders/fragmentShader.glsl");
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));
    GLCall(glUseProgram(program));


    GLCall(GLint posAttr = glGetAttribLocation(program, "position"));
    // std::cout << "Position Attirbute: " << posAttr << std::endl;

    GLCall(glEnableVertexAttribArray(posAttr));
    GLCall(glVertexAttribPointer(posAttr, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

    unsigned int indexBuffer;
    GLCall(glGenBuffers(1, &indexBuffer));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indicies, GL_STATIC_DRAW));


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
        SetUniformVector4(program, "u_Color", redColor, 0.3f, 0.8f, 1.f);
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        if (redColor > 1.f || redColor < 0.f)
            increment = -increment;

        redColor += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    GLCall(glDeleteProgram(program));

    glfwTerminate();
    return 0;
}
