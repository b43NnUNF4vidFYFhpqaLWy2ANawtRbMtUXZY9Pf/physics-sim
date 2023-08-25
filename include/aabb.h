#pragma once

#include "polygon.h"
#include <memory>

struct AABB
{
    Vector2 min, max;
    
    AABB() = default;
    AABB(const Polygon& polygon);

    bool collides(const AABB& other) const;
    bool contains(const AABB& other) const;
    AABB Union(AABB* other) const;
    float area() const;
};
