#pragma once

#include "collision_solver.h"

namespace Physics
{
    class ContactConstraintSolver : public CollisionSolver
    {
    private:
        unsigned m_iterations;
        float slop_p;
        float slop_r;
        float beta;
    public:
        ContactConstraintSolver(unsigned iterations, float slop_p, float slop_, float beta);
        void solve(std::vector<CollisionPair>& collisions, float dt) override;
    };
}
