#ifndef __SHADER_H__
#define __SHADER_H__

//TODO: don't have glm types here?
#include <glm/glm.hpp>

class Shader
{
public:
    Shader();
    void Use();
    void Compile(const char *vertexSource, const char *fragmentSource);
    void SetFloat(const char *name, float value) const;
    void SetInteger(const char *name, int value) const;
    void SetVector2f(const char *name, const glm::vec2 value) const;
    void SetVector3f(const char *name, const glm::vec3 value) const;
    void SetVector4f(const char *name, const glm::vec4 value) const;
    void SetMatrix4(const char *name, const glm::mat4 matrix) const;

private:
    unsigned int id;
    void CheckCompileErrors(unsigned int object, const char *type);
};

#endif
