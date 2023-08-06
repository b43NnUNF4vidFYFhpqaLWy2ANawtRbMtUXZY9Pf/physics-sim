#pragma once

#include "collision.h"
#include <vector>

class CollisionSolver
{
public:
    virtual void solve(std::vector<Collision>& collisions, double dt) = 0;
};