#pragma once

#include "collision_detector.h"

namespace Physics::Collision::Detection::Broadphase::Bruteforce
{
    class Bruteforce : public Physics::Collision::Detection::CollisionDetector
    {
        void update() override;
        void insert(Physics::Dynamics::CollisionBody* body) override;
        void remove(Physics::Dynamics::CollisionBody* body) override;
        std::vector<Physics::Collision::CollisionPair> query(Physics::Dynamics::CollisionBody* const body) const override;
        std::vector<Physics::Collision::CollisionPair> get_collisions() const override;
    };
}