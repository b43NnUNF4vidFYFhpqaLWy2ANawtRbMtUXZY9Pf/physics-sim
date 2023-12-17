#include "collision_detector.h"

namespace Physics
{
    void CollisionDetector::set_objects(std::vector<CollisionBody*>* objects)
    {
        m_objects = objects;
    }
}