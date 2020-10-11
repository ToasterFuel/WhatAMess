#include "Shader.h"

#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader()
{
}

void Shader::Use()
{
    glUseProgram(id);
}

void Shader::Compile(ShaderData& shaderData)
{
    const char* vertexShader = shaderData.GetVertexShader();
    const char* fragmentShader = shaderData.GetFragmentShader();
    unsigned int vertShaderId, fragShaderId;

    vertShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShaderId, 1, &vertexShader, NULL);
    glCompileShader(vertShaderId);
    CheckCompileErrors(vertShaderId, "VERTEX");

    fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShaderId, 1, &fragmentShader, NULL);
    glCompileShader(fragShaderId);
    CheckCompileErrors(fragShaderId, "FRAGMENT");

    id = glCreateProgram();
    glAttachShader(id, vertShaderId);
    glAttachShader(id, fragShaderId);
    glLinkProgram(id);
    CheckCompileErrors(id, "PROGRAM");

    glDeleteShader(vertShaderId);
    glDeleteShader(fragShaderId);
}

void Shader::SetFloat(const char *name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name), value);
}

void Shader::SetInteger(const char *name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name), value);
}

void Shader::SetVector2f(const char *name, const glm::vec2 value) const
{
    glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
}

void Shader::SetVector3f(const char *name, const glm::vec3 value) const
{
    glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const char *name, const glm::vec4 value) const
{
    glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char *name, const glm::mat4 matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, false, glm::value_ptr(matrix));
}

void Shader::CheckCompileErrors(unsigned int object, const char *type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}
