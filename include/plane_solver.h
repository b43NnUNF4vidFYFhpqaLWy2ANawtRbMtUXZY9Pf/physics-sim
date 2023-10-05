#pragma once

#include "collision_solver.h"

namespace Physics::Collision::Resolution::Constraints
{
    class PlaneConstraintSolver : public CollisionSolver
    {
    private:
        unsigned m_iterations;
        float beta;
    public:
        PlaneConstraintSolver(unsigned iterations, float beta);
        void solve(std::vector<Physics::Collision::CollisionPair>& collisions, float dt) override;
    };
}