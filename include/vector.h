#pragma once

struct Vector3
{
    float x, y, z;

    Vector3(float x, float y, float z);
    
    Vector3 operator+(Vector3& other) const;
    Vector3 operator/(float divisor) const;
    Vector3 operator*(float scalar) const;
    friend Vector3 operator*(float scalar, const Vector3& v);
    float dot(Vector3& other) const;
    Vector3 cross(const Vector3& other) const;
};