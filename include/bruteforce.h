#pragma once

#include "collision_detector.h"

namespace Physics
{
    class Bruteforce : public CollisionDetector
    {
    private:
        std::vector<CollisionBody*>* m_objects;
        std::vector<CollisionPair> m_collisions;
    public:
        void set_objects(std::vector<CollisionBody*>* objects) override;
        void update() override;
        void insert(CollisionBody* body) override;
        void remove(CollisionBody* body) override;
        std::vector<CollisionPair>& get_collisions() override;
    };
}
