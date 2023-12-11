#pragma once

#include "collision.h"
#include <vector>

namespace Physics
{
    class CollisionSolver
    {
    public:
        virtual void solve(std::vector<CollisionPair>& collisions, float dt) = 0;
    };
}