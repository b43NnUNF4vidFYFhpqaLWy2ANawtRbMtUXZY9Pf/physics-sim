#include "collision_detector.h"

namespace Physics::Collision::Detection
{
    void CollisionDetector::set_objects(std::vector<Physics::Dynamics::CollisionBody*>* objects)
    {
        m_objects = objects;
    }
}