#pragma once

#include "collision_detector.h"

namespace Physics
{
    class Bruteforce : public CollisionDetector
    {
        void update() override;
        void insert(CollisionBody* body) override;
        void remove(CollisionBody* body) override;
        std::vector<CollisionPair>& get_collisions() override;
    };
}
