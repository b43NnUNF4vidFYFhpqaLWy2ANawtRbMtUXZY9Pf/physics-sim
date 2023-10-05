#include "aabb.h"
#include "polygon.h"
#include <limits>
#include <algorithm>

namespace Physics::Collision::Detection::Broadphase::BVH
{
    AABB::AABB(Physics::Math::Polygon& polygon)
    {
        const float inf = std::numeric_limits<float>::infinity();

        float min_x = inf;
        float min_y = inf; 
        float max_x = -inf;
        float max_y = -inf;

        for (const Physics::Math::Vector2& v : polygon.get_vertices()) {
            if (v.x < min_x) {
                min_x = v.x;
            }
            if (v.x > max_x) {
                max_x = v.x;
            }
            if (v.y < min_y) {
                min_y = v.y;
            }
            if (v.y > max_y) {
                max_y = v.y;
            }
        }
        
        min = {min_x, min_y};
        max = {max_x, max_y};
    }

    bool AABB::collides(const AABB& other) const
    {
        return max.x > other.min.x && min.x < other.max.x
            && max.y > other.min.y && min.y < other.max.y;
    }

    bool AABB::contains(const AABB& other) const
    {
        return other.min.x >= min.x && other.max.x <= max.x
            && other.min.y >= min.y && other.max.y <= max.y;
    }

    AABB AABB::Union(AABB* other) const
    {
        AABB c;
        
        c.min.x = std::min(min.x, other->min.x);
        c.min.y = std::min(min.y, other->min.y);
        c.max.x = std::max(max.x, other->max.x);
        c.max.y = std::max(max.y, other->max.y);

        return c;
    }

    float AABB::area() const
    {
        Physics::Math::Vector2 d = max - min;
        
        return d.x*d.y;
    }
}