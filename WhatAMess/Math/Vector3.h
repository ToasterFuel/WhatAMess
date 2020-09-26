#ifndef __VECTOR_3__
#define __VECTOR_3__

#include <glm/vec3.hpp>

struct Vector3
{
public:
    float x;
    float y;
    float z;
    Vector3(float x, float y, float z);
    Vector3(float x, float y);
    Vector3();
    glm::vec3 ToGraphicsRepresentation();
    Vector3 operator+(const Vector3& other) const;
    Vector3& operator+=(const Vector3& other);
    Vector3 operator-(const Vector3& other) const;
    Vector3& operator-=(const Vector3& other);
    Vector3 operator*(const float& scalar) const;
    Vector3& operator*=(const float& scalar);

    static Vector3 Cross(const Vector3& a, const Vector3& b);
};

#endif