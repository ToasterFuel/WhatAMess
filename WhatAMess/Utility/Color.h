#ifndef __COLOR_H__
#define __COLOR_H__

#include <glm/glm.hpp>

class Color
{
public:
    Color();
    Color(float r, float g, float b, float a);
    void SetColors(float r, float g, float b, float a);
    void SetColorsWith255(float r, float g, float b, float a);
    glm::vec4 ToVec4() const;

    float r;
    float g;
    float b;
    float a;
};

#endif
