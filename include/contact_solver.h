#pragma once

#include "collision_solver.h"

class ContactConstraintSolver : public CollisionSolver
{
private:
    unsigned m_iterations;
    float beta;
public:
    ContactConstraintSolver(unsigned iterations, float beta);
    void solve(std::vector<Collision>& collisions, double dt) override;
};