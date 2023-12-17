#include "vector.h"
#include <cmath>

namespace Physics
{
    Vector2::Vector2() : x(0.0f), y(0.0f), z(0.0f) {}

    Vector2::Vector2(float x, float y) : x(x), y(y), z(0) {}

    Vector2::Vector2(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector2 Vector2::operator+(const Vector2& other) const
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector2& Vector2::operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    Vector2 Vector2::operator-(const Vector2& other) const
    {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vector2 Vector2::operator/(float divisor) const
    {
        return {x/divisor, y/divisor, z/divisor};
    }

    Vector2 Vector2::operator*(float scalar) const
    {
        return {scalar*x, scalar*y, scalar*z};
    }

    Vector2& Vector2::operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;

        return *this;
    }

    Vector2 operator*(float scalar, const Vector2& v)
    {
        return v*scalar;
    }

    float Vector2::dot(const Vector2& other) const
    {
        return x*other.x + y*other.y + z*other.z;
    }

    Vector2 Vector2::cross(const Vector2& other) const
    {
        return {y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x};
    }

    float Vector2::mag()
    {
        return sqrt(this->dot(*this));
    }

    Vector2 Vector2::norm()
    {
        return (*this)/mag();
    }
}