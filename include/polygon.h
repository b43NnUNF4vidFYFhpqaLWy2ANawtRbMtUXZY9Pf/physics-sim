#pragma once

#include <vector>
#include <initializer_list>
#include "vector.h"

struct Polygon
{
public:
    std::vector<Vector3> m_vertices;
    Vector3 m_centroid;
    
    Polygon(std::initializer_list<Vector3> vertices);
    void move(Vector3& delta);
    void rotate(float v);
    bool is_convex() const;
    
    std::vector<Vector3>& get_vertices();
    Vector3& get_centroid();
private:
    Vector3 find_centroid() const;
};