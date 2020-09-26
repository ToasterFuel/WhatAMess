#ifndef __VECTOR_3__
#define __VECTOR_3__

#include <iostream>
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
    Vector3 operator/(const float& scalar) const;
    Vector3& operator/=(const float& scalar);
    friend std::ostream& operator<<(std::ostream &out, const Vector3& vector);

    static const Vector3 UP;
    static const Vector3 RIGHT;
    static const Vector3 FORWARD;

    static Vector3 Cross(const Vector3& a, const Vector3& b);
    static Vector3 Normalize(const Vector3& vector);
    static float Magnitude(const Vector3& vector);
};

#endif