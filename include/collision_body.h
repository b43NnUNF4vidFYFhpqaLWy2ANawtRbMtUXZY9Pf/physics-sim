#pragma once

#include "polygon.h"
#include <memory>

namespace Physics
{
    struct Node;

    class CollisionBody
    {
    protected:
        Polygon m_polygon;
    public:
        std::shared_ptr<Node> m_node;

        CollisionBody(Polygon polygon);
        virtual ~CollisionBody() = default; // Neccessary for dynamic_cast
        Polygon& get_polygon();
    };
}