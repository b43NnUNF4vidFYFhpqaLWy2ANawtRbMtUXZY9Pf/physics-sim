#pragma once

#include "aabb.h"
#include "collision_body.h"
#include <memory>

namespace Physics::Collision::Detection::Broadphase::BVH
{
    struct Node : public std::enable_shared_from_this<Node>
    {
        std::shared_ptr<Node> parent;
        std::shared_ptr<Node> left_child;
        std::shared_ptr<Node> right_child;
        
        AABB enlarged;
        Physics::Dynamics::CollisionBody* body;
        
        Node();

        bool is_leaf() const;
        void make_branch(std::shared_ptr<Node>& a, std::shared_ptr<Node>& b);
        void make_leaf(Physics::Dynamics::CollisionBody* body);
        void refit_AABB(float margin);
        std::shared_ptr<Node>& get_sibling() const;
    };
}