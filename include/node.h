/**
 * @file node.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The Node class represents a node in the AABB tree.
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "aabb.h"
#include "collision_body.h"
#include <memory>

namespace Physics
{
    /**
     * @brief The Node class represents a node in the AABB tree.
     * 
     * A leaf node is the AABB of a CollisionBody, while a branch node is the AABB of its children.
     */
    struct Node : public std::enable_shared_from_this<Node>
    {
        std::shared_ptr<Node> parent; /**< The parent node */
        std::shared_ptr<Node> left_child; /**< The left child node */
        std::shared_ptr<Node> right_child; /**< The right child node */
        bool children_crossed; /**< Flag to indicate if the children have been crossed-chcked*/
        
        AABB enlarged; /**< The (enlarged) AABB of this node */
        CollisionBody* body; /**< The CollisionBody, if this is a leaf */
        
        Node();

        /**
         * @brief Check if the node is a leaf
         * 
         * @return True if the node is a leaf
         */
        bool is_leaf() const;

        /**
         * @brief Make this node a branch with two children
         * 
         * @param a The left child
         * @param b The right child
         */
        void make_branch(std::shared_ptr<Node>& a, std::shared_ptr<Node>& b);

        /**
         * @brief Make this node a leaf with a CollisionBody
         * 
         * @param body The CollisionBody
         */
        void make_leaf(CollisionBody* body);
        
        /**
         * @brief Refit the AABB of this node
         * 
         * @param margin The margin to add to the AABB
         */
        void refit_AABB(float margin);
        
        /**
         * @brief Get the sibling of this node
         * 
         * @return The sibling
         */
        std::shared_ptr<Node>& get_sibling() const;
    };
}
