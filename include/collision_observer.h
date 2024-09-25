#pragma once

#include "collision.h"

namespace Physics
{
    struct CollisionPair;

    class CollisionObserver
    {
    public:
        virtual ~CollisionObserver() {};
        virtual void on_collision(const CollisionPair& collision) = 0;
    };
}