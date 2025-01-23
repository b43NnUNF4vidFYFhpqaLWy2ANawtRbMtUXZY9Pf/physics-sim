/**
 * @file collision_detector.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The CollisionDetector interface represents a collision detector.
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "collision_body.h"
#include "collision.h"

namespace Physics
{
    /**
     * @brief The CollisionDetector interface represents a collision detector.
     * 
     * Implementations of this interface are supposed to be broadphase algorithms.
     */
    class CollisionDetector
    {
    public:
        virtual ~CollisionDetector() {};
        
        /**
         * @brief Insert the objects into the collision detector
         * 
         * @param objects
         */
        virtual void set_objects(std::vector<CollisionBody*>* objects) = 0;

        /**
         * @brief Update the collision detector
         * 
         * @note This function should be called before get_collisions.
         */
        virtual void update() = 0;

        /**
         * @brief Insert a body into the collision detector
         * 
         * @param body
         */
        virtual void insert(CollisionBody* body) = 0;

        /**
         * @brief Remove a body from the collision detector
         * 
         * @param body
         */
        virtual void remove(CollisionBody* body) = 0;

        /**
         * @brief Get the collisions
         * 
         * @return The collisions
         */
        virtual std::vector<CollisionPair>& get_collisions() = 0;
    };
}
