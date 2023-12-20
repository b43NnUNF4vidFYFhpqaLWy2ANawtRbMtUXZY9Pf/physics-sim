#pragma once

#include "collision_body.h"
#include "collision.h"

namespace Physics
{
    class CollisionDetector
    {
    protected:
        std::vector<CollisionBody*>* m_objects;
        std::vector<CollisionPair> m_collisions; // Persistent vector to not heap-allocate every frame
    public:
        void set_objects(std::vector<CollisionBody*>* objects);
        virtual void update() = 0;
        virtual void insert(CollisionBody* body) = 0;
        virtual void remove(CollisionBody* body) = 0;
        virtual std::vector<CollisionPair>& get_collisions() = 0;
    };
}
