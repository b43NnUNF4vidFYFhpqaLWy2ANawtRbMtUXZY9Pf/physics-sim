#pragma once

#include "vector.h"

namespace Physics::Math
{
    class Polygon;
}

namespace Physics::Collision::Detection::Broadphase::BVH
{
    struct AABB
    {
        Physics::Math::Vector2 min, max;
        
        AABB() = default;
        AABB(Physics::Math::Polygon& polygon);

        bool collides(const AABB& other) const;
        bool contains(const AABB& other) const;
        AABB Union(AABB* other) const;
        float area() const;
    };
}