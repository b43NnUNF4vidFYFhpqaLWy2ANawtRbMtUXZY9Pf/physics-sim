#pragma once

#include "collision_body.h"
#include "collision.h"

namespace Physics
{
    class CollisionDetector
    {
    protected:
        std::vector<CollisionBody*>* m_objects;
    public:
        void set_objects(std::vector<CollisionBody*>* objects);
        virtual void update() = 0;
        virtual void insert(CollisionBody* body) = 0;
        virtual void remove(CollisionBody* body) = 0;
        virtual std::vector<CollisionPair> query(CollisionBody* const body) const = 0;
        virtual std::vector<CollisionPair> get_collisions() const = 0;
    };
}