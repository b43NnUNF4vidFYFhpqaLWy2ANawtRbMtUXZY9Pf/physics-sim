#pragma once

#include "aabb.h"
#include "polygon.h"
#include <memory>

namespace Physics
{
    struct Node;

    class CollisionBody : public Polygon
    {
    private:
        AABB m_box;
        std::shared_ptr<Node> m_node;
    public:
        CollisionBody(std::vector<Vector2> vertices);
        virtual ~CollisionBody() = default; // Neccessary for dynamic_cast

        void update_AABB();
        const AABB& get_AABB() const;
        void set_AABB(const AABB& box);

        std::shared_ptr<Node>& get_node();
        void set_node(std::shared_ptr<Node> node);
    };
}
