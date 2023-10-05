#pragma once

#include "collision_detector.h"
#include "node.h"
#include "collision_body.h"

namespace Physics::Collision::Detection::Broadphase::BVH
{
    class AABBTree : public Physics::Collision::Detection::CollisionDetector
    {
    private:
        std::shared_ptr<Node> m_root;
        float m_margin;
        
        std::vector<std::shared_ptr<Node>> get_invalid_nodes(std::shared_ptr<Node>& root);
        void insert_node(std::shared_ptr<Node>& node, std::shared_ptr<Node>& parent);
        void remove_node(std::shared_ptr<Node>& node);
    public:
        AABBTree(float margin);
        
        void update() override;
        void insert(Physics::Dynamics::CollisionBody* body) override;
        void remove(Physics::Dynamics::CollisionBody* body) override;
        std::vector<Physics::Collision::CollisionPair> query(Physics::Dynamics::CollisionBody* const body) const override;
        std::vector<Physics::Collision::CollisionPair> get_collisions() const override;
    };
}