#pragma once

#include "polygon.h"
#include <memory>

namespace Physics::Collision::Detection::Broadphase::BVH
{
    struct Node;
}

namespace Physics::Dynamics
{
    class CollisionBody
    {
    protected:
        Physics::Math::Polygon m_polygon;
    public:
        std::shared_ptr<Physics::Collision::Detection::Broadphase::BVH::Node> m_node;

        CollisionBody(Physics::Math::Polygon polygon);
        virtual ~CollisionBody() = default; // Neccessary for dynamic_cast
        Physics::Math::Polygon& get_polygon();
    };
}