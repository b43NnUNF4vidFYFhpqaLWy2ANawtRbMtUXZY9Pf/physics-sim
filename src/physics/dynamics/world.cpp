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

void World::add_object(CollisionBody* object)
{
    m_objects.push_back(object);
}

void World::remove_object(CollisionBody* object)
{
    if (!object) return;
    
    auto itr = std::find(m_objects.begin(), m_objects.end(), object);
    if ( itr == m_objects.end() ) return;
    
    m_objects.erase(itr);
}

const std::vector<CollisionBody*>& World::get_objects() const
{
    return m_objects;
}

void World::set_gravity(const Vector2& gravity)
{
    m_gravity = gravity;
}

void World::step(double dt)
{
    for (CollisionBody* object : m_objects) {
        RigidBody* rigid_body = dynamic_cast<RigidBody*>(object);

        if (rigid_body) {
            rigid_body->apply_force(rigid_body->get_mass()*m_gravity, rigid_body->get_polygon().get_centroid());
            rigid_body->step(dt);
        }
    }
}