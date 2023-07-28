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
    if ( !is_convex() ) { throw std::invalid_argument("Polygon should be convex"); }
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
    Vector3 centered, i_scaled, j_scaled;

    for (Vector3& vertex : m_vertices) {
        centered = vertex - m_centroid;
        i_scaled = centered.x*i;
        j_scaled = centered.y*j;

        vertex = (i_scaled + j_scaled) + m_centroid;
    }
}

bool Polygon::is_convex() const
{
    return true; // Not implemented
}

std::vector<Vector3>& Polygon::get_vertices()
{
    return m_vertices;
}

Vector3& Polygon::get_centroid()
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