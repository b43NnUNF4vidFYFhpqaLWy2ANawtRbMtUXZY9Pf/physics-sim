#include "polygon.h"
#include "vector.h"
#include <initializer_list>
#include <stdexcept>
#include <cmath>
#include <cstddef>

Polygon::Polygon(std::initializer_list<Vector3> vertices)
    : m_vertices(vertices),
      m_centroid(find_centroid())
{
    if (!is_convex()) {
        throw std::invalid_argument("Polygon should be convex");
    }
}

void Polygon::move(Vector3& delta)
{
    m_centroid += delta;
    
    for (Vector3& vertex : m_vertices) {
        vertex += delta;
    }
}

void Polygon::rotate(float v)
{
    Vector3 i(cos(v), sin(v), 0);
    Vector3 j(-sin(v), cos(v), 0);
    Vector3 centered;

    for (Vector3& vertex : m_vertices) {
        centered = vertex - m_centroid;
        vertex = (centered.x*i + centered.y*j) + m_centroid;
    }
}

bool Polygon::is_convex() const
{
    std::size_t n = m_vertices.size();
    std::size_t prev = n-1;
    Vector3 i_vert, prev_vert, next_vert, a, b;
    float cp;

    for (std::size_t i = 0; i < n; i++) {
        i_vert = m_vertices[i];
        prev_vert = m_vertices[prev];
        next_vert = m_vertices[(i+1) % n];
        
        a = prev_vert - i_vert;
        b = next_vert - i_vert;
        if (a.cross(b).z < 0) return false;

        prev = i;
    }

    return true;
}

const std::vector<Vector3>& Polygon::get_vertices() const
{
    return m_vertices;
}

const Vector3& Polygon::get_centroid() const
{
    return m_centroid;
}

Vector3 Polygon::find_centroid() const
{
    Vector3 centroid;
    float a = 0, addend_second_factor = 0;
    int i_next;
    std::size_t n = m_vertices.size();

    i_next = 1;
    for (int i = 0; i < n; i++) {
        Vector3 v = m_vertices[i];
        Vector3 v1 = m_vertices[i_next];
        
        addend_second_factor = v.x*v1.y - v1.x*v.y;
        centroid.x += (v.x + v1.x)*addend_second_factor;
        centroid.y += (v.y + v1.y)*addend_second_factor;
        a += v.x*v1.y - v1.x*v.y;
        
        i_next = (i_next + 1) % n;
    }

    a /= 2;
    centroid.x /= 6.0*a;
    centroid.y /= 6.0*a;
    
    return centroid;
}