#pragma once

#include "polygon.h"
#include <memory>

namespace Physics
{
    struct Node;

    class CollisionBody : public Polygon
    {
    public:
        std::shared_ptr<Node> m_node;

        CollisionBody(std::vector<Vector2> vertices);
        virtual ~CollisionBody() = default; // Neccessary for dynamic_cast
    };
}