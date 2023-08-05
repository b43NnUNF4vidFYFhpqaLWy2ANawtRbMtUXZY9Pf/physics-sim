#pragma once

#include "vector.h"
#include "polygon.h"
#include <array>
#include <initializer_list>

struct CSOSupport
{
    Vector2 a, b, c;
    
    CSOSupport();
    CSOSupport(const Polygon& a, const Polygon& b, Vector2 d);
};

struct Simplex2
{
private:
    std::array<CSOSupport, 3> m_points;
    unsigned m_size;
    bool m_contains_origin;
public:
    Simplex2();
    Simplex2& operator=(std::initializer_list<CSOSupport> points);
    void push_front(CSOSupport point);
    CSOSupport& operator[](unsigned i);
    unsigned size() const;
    void set_contains_origin();
    bool contains_origin() const;
};