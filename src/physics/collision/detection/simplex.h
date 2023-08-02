#pragma once

#include "vector.h"
#include "polygon.h"
#include <array>
#include <initializer_list>

struct Simplex2
{
private:
    std::array<Vector2, 3> m_points;
    unsigned m_size;
    bool m_contains_origin;
public:
    Simplex2();
    Simplex2& operator=(std::initializer_list<Vector2> points);
    void push_front(Vector2 point);
    Vector2& operator[](unsigned i);
    unsigned size() const;
    void set_contains_origin();
    bool contains_origin() const;
};

Vector2 CSO_support(const Polygon& a, const Polygon& b, Vector2 d);