#include <algorithm>
#include <cstddef>
#include "world.h"
#include "vector.h"
#include "rigid_body.h"

World::World() {};

void World::reserve_objects(std::size_t cap)
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

const std::vector<RigidBody*>& World::get_objects() const
{
    return m_objects;
}

void World::set_gravity(const Vector3& gravity)
{
    m_gravity = gravity;
}

void World::step(double dt)
{
    for (RigidBody* object : m_objects) {
        object->apply_force(object->get_mass()*m_gravity, object->get_polygon().get_centroid());
        object->step(dt);
    }
}