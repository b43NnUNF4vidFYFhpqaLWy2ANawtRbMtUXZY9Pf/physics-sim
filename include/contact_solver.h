#pragma once

#include "collision_solver.h"
#include "contact_constraint.h"

namespace Physics
{
    class ContactConstraintSolver : public CollisionSolver
    {
    private:
        unsigned m_iterations;
        float slop_p;
        float slop_r;
        float beta;

        std::vector<ContactConstraint> m_constraints;
    public:
        ContactConstraintSolver(unsigned iterations, float slop_p, float slop_, float beta);
        void solve(std::vector<CollisionPair>& collisions, float dt) override;
    };
}
