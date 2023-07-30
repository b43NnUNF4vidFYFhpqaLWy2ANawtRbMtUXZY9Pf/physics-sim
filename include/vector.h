#pragma once

struct Vector3
{
    float x, y, z;

    Vector3();
    Vector3(float x, float y, float z);
    
    Vector3 operator+(const Vector3& other) const;
    Vector3& operator+=(const Vector3& other);
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator/(float divisor) const;
    Vector3 operator*(float scalar) const;
    friend Vector3 operator*(float scalar, const Vector3& v);
    float dot(const Vector3& other) const;
    Vector3 cross(const Vector3& other) const;
};