#pragma once

#include "collision_solver.h"

namespace Physics
{
    class ContactConstraintSolver : public CollisionSolver
    {
    private:
        unsigned m_iterations;
        float beta;
    public:
        ContactConstraintSolver(unsigned iterations, float beta);
        void solve(std::vector<CollisionPair>& collisions, float dt) override;
    };
}