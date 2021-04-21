#include "Shader.h"

#include <string.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#ifdef OPEN_GL_BUILD
#include <glad/glad.h>
#elif WEB_GL_BUILD
#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>
#endif

Shader::Shader()
{
}

void Shader::Use() const
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

int Shader::GetUniformLocation(const char* name) const
{
    return glGetUniformLocation(id, name);
}

void Shader::SetFloat(const char *name, float value) const
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetInteger(const char *name, int value) const
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetVector2f(const char *name, const glm::vec2 value) const
{
    glUniform2f(GetUniformLocation(name), value.x, value.y);
}

void Shader::SetVector3f(const char *name, const glm::vec3 value) const
{
    glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const char *name, const glm::vec4 value) const
{
    glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char *name, const glm::mat4 matrix) const
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, false, glm::value_ptr(matrix));
}

void Shader::CheckCompileErrors(unsigned int id, const char *type)
{
    int success;
    char infoLog[1024];
    if(strcmp(type, "PROGRAM") != 0)
    {
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(id, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER: Compile-time error: Type: " << type << "\n" << infoLog << "\n++++++\n";
            glGetProgramInfoLog(id, 1024, NULL, infoLog);
            std::cout << infoLog << "\n-------------------------------------------------------\n";
        }
    }
    else
    {
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(id, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER: Link-time error: Type: " << type << "\n" << infoLog << "\n++++++\n";
            glGetProgramInfoLog(id, 1024, NULL, infoLog);
            std::cout << infoLog << "\n-------------------------------------------------------\n";
        }
    }
}
