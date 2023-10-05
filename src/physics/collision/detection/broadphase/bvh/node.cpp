#include "node.h"

namespace Physics::Collision::Detection::Broadphase::BVH
{
    Node::Node()
        : parent(nullptr),
          left_child(nullptr),
          right_child(nullptr),
          body(nullptr)
    {}

    bool Node::is_leaf() const
    {
        return !left_child && !right_child;
    }

    void Node::make_branch(std::shared_ptr<Node>& a, std::shared_ptr<Node>& b)
    {
        a->parent = shared_from_this();
        b->parent = shared_from_this();
        
        left_child = a;
        right_child = b;
    }

    void Node::make_leaf(Physics::Dynamics::CollisionBody* body)
    {
        Physics::Math::Polygon& polygon = body->get_polygon();
        AABB box(polygon);
        polygon.set_AABB(box);

        left_child = nullptr;
        right_child = nullptr;
        
        this->body = body;
        body->m_node = shared_from_this();
    }

    void Node::refit_AABB(float margin)
    {
        if ( is_leaf() ) {
            const AABB& tight = body->get_polygon().get_AABB();
            const Physics::Math::Vector2 margin_vec = {margin, margin};
            enlarged.min = tight.min - margin_vec;
            enlarged.max = tight.max + margin_vec;
        } else {
            enlarged = left_child->enlarged.Union( &(right_child->enlarged) );
        }
    }

    std::shared_ptr<Node>& Node::get_sibling() const
    {
        return shared_from_this() == parent->left_child ? parent->right_child : parent->left_child;
    }
}