/**
 * @file collision_body.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The CollisionBody class represents a polygon with collision detection capabilities.
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "aabb.h"
#include "polygon.h"
#include "collision_notifier.h"

#include <functional>
#include <memory>

namespace Physics
{
    struct CollisionPair;
    struct Node;

    /**
     * @brief The CollisionBody class represents a polygon with collision detection capabilities.
     * 
     */
    class CollisionBody : public Polygon, public CollisionNotifier
    {
    private:
        std::function<void(CollisionPair&, float)> m_onCollision;

        AABB m_box;
        std::shared_ptr<Node> m_node;
    public:
        /**
         * @brief Construct a new CollisionBody object
         * 
         * @param vertices The vertices of the polygon
         * 
         * @pre The vertices should be in counter-clockwise order and the polygon should be convex (use is_convex() to check)
         */
        CollisionBody(std::vector<Vector2> vertices);

        virtual ~CollisionBody() = default; // Neccessary for dynamic_cast

        /**
         * @brief Get the collision callback
         * 
         * @return The collision callback
         */
        const std::function<void(CollisionPair&, float)>& get_collision_callback() const;

        /**
         * @brief Set the collision callback
         * 
         * The callback will be called when a collision occurs and receives the collision pair and the time step.
         * 
         * @param callback
         */
        void set_collision_callback(const std::function<void(CollisionPair&, float)>& callback);

        /**
         * @brief Update the AABB
         * 
         */
        void update_AABB();

        /**
         * @brief Get the AABB
         * 
         * @return The AABB
         */
        const AABB& get_AABB() const;

        /**
         * @brief Set the AABB
         * 
         * @param box
         */
        void set_AABB(const AABB& box);

        /**
         * @brief Get the AABB node
         * 
         * @return The node
         */
        std::shared_ptr<Node>& get_node();

        /**
         * @brief Set the AABB node
         * 
         * @param node
         */
        void set_node(std::shared_ptr<Node> node);
    };
}
