#pragma once

#include "polygon.h"

class CollisionBody
{
protected:
    Polygon m_polygon;
public:
    CollisionBody(Polygon polygon);
    virtual ~CollisionBody() {}; // Neccessary for dynamic_cast
    const Polygon& get_polygon() const;
};