#include "collision_detector.h"

void CollisionDetector::set_objects(std::vector<CollisionBody*>* objects)
{
    m_objects = objects;
}