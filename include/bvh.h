#pragma once

#include "collision_detector.h"
#include "node.h"
#include "collision_body.h"

class AABBTree : public CollisionDetector
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
    void insert(CollisionBody* body) override;
    void remove(CollisionBody* body) override;
    std::vector<Collision> query(CollisionBody* const body) const override;
    std::vector<Collision> get_collisions() const override;
};