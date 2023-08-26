#pragma once

#include "node.h"
#include "collision_body.h"

class AABBTree
{
private:
    std::shared_ptr<Node> m_root;
    float m_margin;
    
    std::vector<std::shared_ptr<Node>> get_invalid_nodes(std::shared_ptr<Node>& root, std::size_t objects);
    void insert_node(std::shared_ptr<Node>& node, std::shared_ptr<Node>& parent);
    void remove_node(std::shared_ptr<Node>& node);
public:
    AABBTree(float margin);
    
    void update(std::size_t objects);
    void insert(CollisionBody* body);
    void remove(CollisionBody* body);
};