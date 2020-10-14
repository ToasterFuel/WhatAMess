#include "Color.h"

Color::Color(): r(1.0), g(1.0), b(1.0), a(1.0)
{
}

Color::Color(float r, float g, float b, float a): r(r), g(g), b(b), a(a)
{
}

void Color::SetColors(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Color::SetColorsWith255(float r, float g, float b, float a)
{
    SetColors(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
}

glm::vec4 Color::ToVec4() const
{
    return glm::vec4(r, g, b, a);
}