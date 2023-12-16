#pragma once

#include "aabb.h"
#include "polygon.h"
#include <memory>

namespace Physics
{
    struct Node;

    class CollisionBody : public Polygon
    {
    public:
        std::shared_ptr<Node> m_node;
        AABB m_box;

        CollisionBody(std::vector<Vector2> vertices);
        virtual ~CollisionBody() = default; // Neccessary for dynamic_cast

        void update_AABB();
        const AABB& get_AABB() const;
        void set_AABB(const AABB& box);
    };
}
