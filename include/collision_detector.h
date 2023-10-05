#pragma once

#include "collision_body.h"
#include "collision.h"

namespace Physics::Collision::Detection
{
    class CollisionDetector
    {
    protected:
        std::vector<Physics::Dynamics::CollisionBody*>* m_objects;
    public:
        void set_objects(std::vector<Physics::Dynamics::CollisionBody*>* objects);
        virtual void update() = 0;
        virtual void insert(Physics::Dynamics::CollisionBody* body) = 0;
        virtual void remove(Physics::Dynamics::CollisionBody* body) = 0;
        virtual std::vector<Physics::Collision::CollisionPair> query(Physics::Dynamics::CollisionBody* const body) const = 0;
        virtual std::vector<Physics::Collision::CollisionPair> get_collisions() const = 0;
    };
}