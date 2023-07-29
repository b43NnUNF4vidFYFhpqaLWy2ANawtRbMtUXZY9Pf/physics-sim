#pragma once

#include <vector>
#include <initializer_list>
#include "vector.h"

class Polygon
{
private:
    std::vector<Vector3> m_vertices;
    Vector3 m_centroid;

    Vector3 find_centroid() const;
public:
    Polygon(std::initializer_list<Vector3> vertices);
    void move(Vector3& delta);
    void rotate(float v);
    bool is_convex() const;
    
    const std::vector<Vector3>& get_vertices() const;
    const Vector3& get_centroid() const;
};