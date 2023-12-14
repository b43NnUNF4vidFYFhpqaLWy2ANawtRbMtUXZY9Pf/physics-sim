#include "collision_body.h"

namespace Physics
{
    CollisionBody::CollisionBody(std::vector<Vector2> vertices)
        : Polygon(vertices)
    {
        if (!is_convex()) {
            throw std::invalid_argument("Polygon should be convex");
        }
    }
}
