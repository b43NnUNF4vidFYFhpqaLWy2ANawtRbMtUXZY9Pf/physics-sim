#pragma once

#include "collision_observer.h"

namespace Engine
{
    class CollisionLogger : public Physics::CollisionObserver
    {
        void on_collision(const Physics::CollisionPair& collision) override;
    };
}