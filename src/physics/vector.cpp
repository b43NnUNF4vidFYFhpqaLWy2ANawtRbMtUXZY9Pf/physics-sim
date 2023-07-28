#include "vector.h"

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3 Vector3::operator+(Vector3& other) const
{
    return {x + other.x, y + other.y, z + other.z};
}

Vector3& Vector3::operator+=(Vector3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Vector3 Vector3::operator-(Vector3& other) const
{
    return {x - other.x, y - other.y, z - other.z};
}

Vector3 Vector3::operator/(float divisor) const
{
    return {x/divisor, y/divisor, z/divisor};
}

Vector3 Vector3::operator*(float scalar) const
{
    return {scalar*x, scalar*y, scalar*z};
}

Vector3 operator*(float scalar, const Vector3& v)
{
    return v*scalar;
}

float Vector3::dot(Vector3& other) const
{
    return x*other.x + y*other.y + z*other.z;
}

Vector3 Vector3::cross(const Vector3& other) const
{
    return {y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x};
}