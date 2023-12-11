#pragma once

#include "vector.h"

namespace Physics
{
    class Polygon;

    struct AABB
    {
        Vector2 min, max;
        
        AABB() = default;
        AABB(Polygon& polygon);

        bool collides(const AABB& other) const;
        bool contains(const AABB& other) const;
        AABB Union(AABB* other) const;
        float area() const;
    };
}