#include "collision_body.h"

namespace Physics
{
    CollisionBody::CollisionBody(Polygon polygon)
        : m_polygon(polygon)
    {
        if (!m_polygon.is_convex()) {
            throw std::invalid_argument("Polygon should be convex");
        }
    }

    Polygon& CollisionBody::get_polygon()
    {
        return m_polygon;
    }
}