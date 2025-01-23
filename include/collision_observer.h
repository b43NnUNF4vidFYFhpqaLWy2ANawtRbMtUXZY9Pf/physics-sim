/**
 * @file collision_observer.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The CollisionObserver interface listens for collisions.
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "collision.h"

namespace Physics
{
    struct CollisionPair;

    /**
     * @brief The CollisionObserver interface listens for collisions.
     * 
     */
    class CollisionObserver
    {
    public:
        virtual ~CollisionObserver() {};

        /**
         * @brief Callback for observed collisions
         * 
         * @param collision 
         */
        virtual void on_collision(const CollisionPair& collision) = 0;
    };
}