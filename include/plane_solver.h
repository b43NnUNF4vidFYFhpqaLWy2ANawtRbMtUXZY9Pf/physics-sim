#pragma once

#include "collision_solver.h"

class PlaneConstraintSolver : public CollisionSolver
{
private:
    unsigned m_iterations;
    float beta;
public:
    PlaneConstraintSolver(unsigned iterations, float beta);
    void solve(std::vector<Collision>& collisions, float dt) override;
};