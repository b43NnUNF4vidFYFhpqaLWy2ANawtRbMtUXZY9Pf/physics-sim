#pragma once

#include "collision_body.h"
#include "collision.h"

namespace Physics
{
    class CollisionDetector
    {
    public:
        virtual void set_objects(std::vector<CollisionBody*>* objects) = 0;
        virtual void update() = 0;
        virtual void insert(CollisionBody* body) = 0;
        virtual void remove(CollisionBody* body) = 0;
        virtual std::vector<CollisionPair>& get_collisions() = 0;
    };
}
