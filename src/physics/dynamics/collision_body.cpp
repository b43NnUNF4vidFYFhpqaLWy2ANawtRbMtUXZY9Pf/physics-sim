#include "collision_body.h"

CollisionBody::CollisionBody(Polygon polygon)
    : m_polygon(polygon)
{
}

const Polygon& CollisionBody::get_polygon() const
{
    return m_polygon;
}