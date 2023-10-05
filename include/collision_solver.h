#pragma once

#include "collision.h"
#include <vector>

namespace Physics::Collision::Resolution::Constraints
{
    class CollisionSolver
    {
    public:
        virtual void solve(std::vector<Physics::Collision::CollisionPair>& collisions, float dt) = 0;
    };
}