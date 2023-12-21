#pragma once

#include "collision_solver.h"
#include "plane_constraint.h"

namespace Physics
{
    class PlaneConstraintSolver : public CollisionSolver
    {
    private:
        unsigned m_iterations;
        float beta;

        std::vector<PlaneConstraint> m_constraints;
    public:
        PlaneConstraintSolver(unsigned iterations, float beta);
        void solve(std::vector<CollisionPair>& collisions, float dt) override;
    };
}
