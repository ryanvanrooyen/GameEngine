
#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

namespace Game
{

class Shader
{
public:
    Shader(const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath);
    ~Shader();

    bool Compile();
    void Bind() const;
    void Unbind() const;

    void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
    void SetUniform1f(const std::string& name, float v1);
    void SetUniform1i(const std::string& name, int v1);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
    unsigned int rendererId;
    const std::string vertexShaderFilepath;
    const std::string fragmentShaderFilepath;
    std::unordered_map<std::string, int> uniformCache;

    int GetUniformLocation(const std::string& name);
};

}