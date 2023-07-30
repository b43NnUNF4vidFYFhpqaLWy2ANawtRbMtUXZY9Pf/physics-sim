#include "polygon.h"
#include "vector.h"
#include <initializer_list>
#include <stdexcept>
#include <cmath>
#include <cstddef>

Polygon::Polygon(std::initializer_list<Vector2> vertices)
    : m_vertices(vertices),
      m_centroid(find_centroid())
{
    if (!is_convex()) {
        throw std::invalid_argument("Polygon should be convex");
    }
}

void Polygon::move(Vector2& delta)
{
    m_centroid += delta;
    
    for (Vector2& vertex : m_vertices) {
        vertex += delta;
    }
}

void Polygon::rotate(float v)
{
    Vector2 i(cos(v), sin(v));
    Vector2 j(-sin(v), cos(v));
    Vector2 centered;

    for (Vector2& vertex : m_vertices) {
        centered = vertex - m_centroid;
        vertex = (centered.x*i + centered.y*j) + m_centroid;
    }
}

bool Polygon::is_convex() const
{
    std::size_t n = m_vertices.size();
    std::size_t prev = n-1;
    Vector2 i_vert, prev_vert, next_vert, a, b;

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

const std::vector<Vector2>& Polygon::get_vertices() const
{
    return m_vertices;
}

const Vector2& Polygon::get_centroid() const
{
    return m_centroid;
}

Vector2 Polygon::find_centroid() const
{
    Vector2 centroid;
    float a = 0, addend_second_factor = 0;
    int i_next;
    std::size_t n = m_vertices.size();

    i_next = 1;
    for (int i = 0; i < n; i++) {
        Vector2 v = m_vertices[i];
        Vector2 v1 = m_vertices[i_next];
        
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