#include "collision_body.h"

namespace Physics
{
    CollisionBody::CollisionBody(std::vector<Vector2> vertices)
        : Polygon(vertices)
    {
        if (!is_convex()) {
            throw std::invalid_argument("Polygon should be convex");
        }
    }

    const std::function<void(CollisionPair&, float)>& CollisionBody::get_collision_callback() const
    {
        return m_onCollision;
    }

    void CollisionBody::set_collision_callback(const std::function<void(CollisionPair&, float)>& callback)
    {
        m_onCollision = callback;
    }

    void CollisionBody::update_AABB()
    {
        m_box = AABB(this);
    }

    const AABB& CollisionBody::get_AABB() const
    {
        return m_box;
    }

    void CollisionBody::set_AABB(const AABB& box)
    {
        m_box = box;
    }

    std::shared_ptr<Node>& CollisionBody::get_node()
    {
        return m_node;
    }

    void CollisionBody::set_node(std::shared_ptr<Node> node)
    {
        m_node = std::move(node);
    }
}
