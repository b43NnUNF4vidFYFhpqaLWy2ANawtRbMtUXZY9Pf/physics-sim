#include "collision_body.h"

CollisionBody::CollisionBody(Polygon polygon)
    : m_polygon(polygon)
{
}

Polygon& CollisionBody::get_polygon()
{
    return m_polygon;
}