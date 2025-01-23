/**
 * @file plane_solver.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The PlaneConstraintSolver class is responsible for solving plane constraints
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "collision_solver.h"
#include "plane_constraint.h"

namespace Physics
{
    /**
     * @brief The PlaneConstraintSolver class is responsible for solving plane constraints
     * 
     * @see PlaneConstraint
     */
    class PlaneConstraintSolver : public CollisionSolver
    {
    private:
        unsigned m_iterations;
        float beta;

        std::vector<PlaneConstraint> m_constraints;
    public:
        /**
         * @brief Construct a new Plane Constraint Solver object
         * 
         * @param iterations The number of iterations
         * @param beta The Baumgarte stabilization factor
         * 
         * @see PlaneConstraint for more information on the parameters
         */
        PlaneConstraintSolver(unsigned iterations, float beta);
        void solve(std::vector<CollisionPair>& collisions, float dt) override;
    };
}
