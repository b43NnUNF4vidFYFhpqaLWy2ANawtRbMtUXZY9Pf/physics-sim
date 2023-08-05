#pragma once

#include "collision_solver.h"

class ContactConstraintSolver : public CollisionSolver
{
private:
    unsigned m_iterations;
public:
    ContactConstraintSolver(unsigned iterations);
    void solve(std::vector<Collision>* collisions, double dt) override;
};