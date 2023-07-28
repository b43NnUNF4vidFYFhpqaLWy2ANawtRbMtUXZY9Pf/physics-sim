#include <algorithm>
#include <cstddef>
#include "world.h"
#include "vector.h"
#include "rigid_body.h"

World::World() {};

void World::reserve(std::size_t cap)
{
    m_objects.reserve(cap);
}

void World::add_object(RigidBody* object)
{
    m_objects.push_back(object);
}

void World::remove_object(RigidBody* object)
{
    if (!object) return;
    
    auto itr = std::find(m_objects.begin(), m_objects.end(), object);
    if ( itr == m_objects.end() ) return;
    
    m_objects.erase(itr);
}

void World::step(float dt)
{
    for (RigidBody* object : m_objects) {
        object->step(dt);
    }
}