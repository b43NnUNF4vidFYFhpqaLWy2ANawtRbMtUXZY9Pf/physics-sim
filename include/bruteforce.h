#pragma once

#include "collision_detector.h"

class Bruteforce : public CollisionDetector
{
    void update() override;
    void insert(CollisionBody* body) override;
    void remove(CollisionBody* body) override;
    std::vector<Collision> query(CollisionBody* const body) const override;
    std::vector<Collision> get_collisions() const override;
};