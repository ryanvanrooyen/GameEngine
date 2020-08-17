
#include "Shader.hpp"
#include "opengl.hpp"
#include <sstream>
#include <fstream>

using std::string;


Shader::Shader(const string& vertexShaderFilepath, const string& fragmentShaderFilepath)
    : rendererId(0), vertexShaderFilepath(vertexShaderFilepath), fragmentShaderFilepath(fragmentShaderFilepath) {}

Shader::~Shader()
{
    if (rendererId)
    {
        GLCall(glDeleteProgram(rendererId));
    }
}

void Shader::Bind() const
{
    if (!rendererId)
    {
        return;
    }

    GLCall(glUseProgram(rendererId));
    // unsigned int shaderId = compileShaderFile(type, filepath);
    // if (shaderId == 0)
    //     return;

    // GLCall(glAttachShader(programId, shaderId));
    // GLCall(glLinkProgram(program));
    // GLCall(glValidateProgram(program));
    // GLCall(glDeleteShader(shaderId));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (!rendererId)
    {
        return -1;
    }

    const char* nameStr = name.c_str();
    int uniformLocation;
    if (uniformCache.find(name) != uniformCache.end())
    {
         uniformLocation = uniformCache[name];
    }
    else
    {
        INFO("Getting uniform location for \"%s\"", nameStr);
        GLCall(uniformLocation = glGetUniformLocation(rendererId, nameStr));
        uniformCache[name] = uniformLocation;
    }

    ASSERT_WARN(uniformLocation != -1, "Uniform \"%s\" not found", nameStr);
    return uniformLocation;
}

void Shader::SetUniform4f(const string& name, float v1, float v2, float v3, float v4)
{
    if (!rendererId)
    {
        return;
    }
    GLCall(glUniform4f(GetUniformLocation(name), v1, v2, v3, v4));
}

void Shader::SetUniform1f(const string& name, float v1)
{
    if (!rendererId)
    {
        return;
    }
    GLCall(glUniform1f(GetUniformLocation(name), v1));
}

void Shader::SetUniform1i(const string& name, int v1)
{
    if (!rendererId)
    {
        return;
    }
    GLCall(glUniform1i(GetUniformLocation(name), v1));
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
        ERROR("Failed to compile shader: %s: %s", filepath.c_str(), message);
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

bool Shader::Compile()
{
    uniformCache.clear();

    // Delete previous program if exists:
    if (rendererId)
    {
        GLCall(glDeleteProgram(rendererId));
    }

    GLCall(rendererId = glCreateProgram());
    unsigned int vs = compileShaderFile(GL_VERTEX_SHADER, vertexShaderFilepath);
    if (vs == 0)
    {
        GLCall(glDeleteProgram(rendererId));
        rendererId = 0;
        return false;
    }
    unsigned int fs = compileShaderFile(GL_FRAGMENT_SHADER, fragmentShaderFilepath);
    if (fs == 0)
    {
        GLCall(glDeleteProgram(rendererId));
        rendererId = 0;
        return false;
    }

    GLCall(glAttachShader(rendererId, vs));
    GLCall(glAttachShader(rendererId, fs));
    GLCall(glLinkProgram(rendererId));
    GLCall(glValidateProgram(rendererId));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return true;
}

// static ShaderSource ParseShader(const string& filepath)
// {
//     std::ifstream file(filepath);

//     stringstream shaders[2];
//     unsigned int shaderIndex = 0;

//     string line;
//     while (getline(file, line))
//     {
//         if (line.find("#shader") != string::npos)
//         {
//             if (line.find("vertex") != string::npos)
//                 shaderIndex = 0;
//             else if (line.find("fragment") != string::npos)
//                 shaderIndex = 1;
//         }
//         else
//         {
//             shaders[shaderIndex] << line << std::endl;
//         }
//     }

//     return { shaders[0].str(), shaders[1].str() };
// }
