#include <cmath>

#include "Vector3.h"

Vector3::Vector3(float x, float y, float z): x(x), y(y), z(z)
{
};

Vector3::Vector3(float x, float y): x(x), y(y), z(0)
{
};

Vector3::Vector3(): x(0), y(0), z(0)
{
};

glm::vec3 Vector3::ToGraphicsRepresentation()
{
    return glm::vec3(x, y, z);
}

Vector3 Vector3::operator+(const Vector3& other) const
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3& Vector3::operator-=(const Vector3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

Vector3 Vector3::operator*(const float& scalar) const
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3& Vector3::operator*=(const float& scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
}

Vector3 Vector3::operator/(const float& scalar) const
{
    return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3& Vector3::operator/=(const float& scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;

    return *this;
}

Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
{
    float x = a.y * b.z - a.z * b.y;
    float y = a.z * b.x - a.x * b.z;
    float z = a.x * b.y - a.y * b.x;

    return Vector3(x, y, z);
}

float Vector3::Magnitude(const Vector3& vector)
{
    return sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
}

Vector3 Vector3::Normalize(const Vector3& vector)
{
    return vector / Vector3::Magnitude(vector);
}
