#pragma once

namespace Physics::Math
{
    struct Vector2
    {
        float x, y, z;

        Vector2();
        Vector2(float x, float y);
        Vector2(float x, float y, float z);
        
        Vector2 operator+(const Vector2& other) const;
        Vector2& operator+=(const Vector2& other);
        Vector2 operator-(const Vector2& other) const;
        Vector2 operator/(float divisor) const;
        Vector2 operator*(float scalar) const;
        Vector2& operator*=(float scalar);
        friend Vector2 operator*(float scalar, const Vector2& v);
        float dot(const Vector2& other) const;
        Vector2 cross(const Vector2& other) const;
        float mag();
        Vector2 norm();
    };
}