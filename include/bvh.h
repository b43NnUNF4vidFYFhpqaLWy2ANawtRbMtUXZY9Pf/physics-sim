/**
 * @file bvh.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The AABBTree class implements a dynamic AABB tree
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "collision_detector.h"
#include "node.h"
#include "collision_body.h"

namespace Physics
{
    /**
     * @brief The AABBTree class implements a dynamic AABB tree
     * 
     */
    class AABBTree : public CollisionDetector
    {
    private:
        std::shared_ptr<Node> m_root;
        float m_margin;

        std::vector<CollisionBody*>* m_objects;
        std::vector<CollisionPair> m_collisions;
        std::vector<std::shared_ptr<Node>> m_invalids;

        void update_invalid_nodes(std::shared_ptr<Node>& node);
        void insert_node(std::shared_ptr<Node>& node, std::shared_ptr<Node>& parent);
        void remove_node(std::shared_ptr<Node>& node);

        void cross_children(std::shared_ptr<Node>& node);
        void clear_crossed_flags(std::shared_ptr<Node>& node);
        void compute_collisions(std::shared_ptr<Node>& a, std::shared_ptr<Node>& b);
    public:
        /**
         * @brief Construct a new AABBTree object
         * 
         * @param margin The margin for the enlarged AABB. When the AABB moves outside the enlarged AABB, the node is re-inserted.
         */
        AABBTree(float margin);
        
        void set_objects(std::vector<CollisionBody*>* objects) override;
        void update() override;
        void insert(CollisionBody* body) override;
        void remove(CollisionBody* body) override;
        std::vector<CollisionPair>& get_collisions() override;
    };
}
