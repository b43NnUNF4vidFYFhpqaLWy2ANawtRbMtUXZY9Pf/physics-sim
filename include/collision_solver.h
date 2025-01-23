/**
 * @file collision_solver.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The CollisionSolver interface is responsible for solving collisions.
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "collision.h"
#include <vector>

namespace Physics
{
    /**
     * @brief The CollisionSolver interface is responsible for solving collisions.
     * 
     */
    class CollisionSolver
    {
    public:
        /**
         * @brief Resolve collisions
         * 
         * @param collisions 
         * @param dt Time step
         */
        virtual void solve(std::vector<CollisionPair>& collisions, float dt) = 0;
    };
}