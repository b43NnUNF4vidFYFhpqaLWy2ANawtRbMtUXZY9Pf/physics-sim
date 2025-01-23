/**
 * @file contact_solver.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The ContactConstraintSolver class is responsible for solving contact constraints
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "collision_solver.h"
#include "contact_constraint.h"

namespace Physics
{
    /**
     * @brief The ContactConstraintSolver class is responsible for solving contact constraints
     * 
     * @see ContactConstraint
     */
    class ContactConstraintSolver : public CollisionSolver
    {
    private:
        unsigned m_iterations;
        float slop_p;
        float slop_r;
        float beta;

        std::vector<ContactConstraint> m_constraints;
    public:
        /**
         * @brief Construct a new ContactConstraintSolver object
         * 
         * @param iterations The number of iterations
         * @param slop_p Penetration slop
         * @param slop_r Restitution slop
         * @param beta The Baumgarte stabilization factor
         * 
         * @see ContactConstraint for more information on the parameters
         */
        ContactConstraintSolver(unsigned iterations, float slop_p, float slop_r, float beta);
        void solve(std::vector<CollisionPair>& collisions, float dt) override;
    };
}
