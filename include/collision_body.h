#pragma once

#include "aabb.h"
#include "collision.h"
#include "polygon.h"
#include <functional>
#include <memory>

namespace Physics
{
    struct CollisionPair;
    struct Node;

    class CollisionBody : public Polygon
    {
    private:
        std::function<void(CollisionPair&, float)> m_onCollision;

        AABB m_box;
        std::shared_ptr<Node> m_node;
    public:
        CollisionBody(std::vector<Vector2> vertices);
        virtual ~CollisionBody() = default; // Neccessary for dynamic_cast

        const std::function<void(CollisionPair&, float)>& get_collision_callback() const;
        void set_collision_callback(const std::function<void(CollisionPair&, float)>& callback);

        void update_AABB();
        const AABB& get_AABB() const;
        void set_AABB(const AABB& box);

        std::shared_ptr<Node>& get_node();
        void set_node(std::shared_ptr<Node> node);
    };
}
