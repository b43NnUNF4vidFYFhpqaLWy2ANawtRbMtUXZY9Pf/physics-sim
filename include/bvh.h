#pragma once

#include "collision_detector.h"
#include "node.h"
#include "collision_body.h"

namespace Physics
{
    class AABBTree : public CollisionDetector
    {
    private:
        std::shared_ptr<Node> m_root;
        float m_margin;

        std::vector<CollisionPair> m_collisions;
        std::vector<std::shared_ptr<Node>> m_invalids;

        void update_invalid_nodes(std::shared_ptr<Node>& node);
        void insert_node(std::shared_ptr<Node>& node, std::shared_ptr<Node>& parent);
        void remove_node(std::shared_ptr<Node>& node);

        void cross_children(std::shared_ptr<Node>& node);
        void clear_crossed_flags(std::shared_ptr<Node>& node);
        void compute_collisions(std::shared_ptr<Node>& a, std::shared_ptr<Node>& b);
    public:
        AABBTree(float margin);
        
        void update() override;
        void insert(CollisionBody* body) override;
        void remove(CollisionBody* body) override;
        std::vector<CollisionPair>& get_collisions() override;
    };
}
