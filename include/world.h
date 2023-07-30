#pragma once
#include "rigid_body.h"
#include <vector>
#include <cstddef>

class World
{
private:
    std::vector<RigidBody*> m_objects;
    Vector3 m_gravity;
public:
    World();

    void reserve_objects(std::size_t cap);
    void add_object(RigidBody* object);
    void remove_object(RigidBody* object);
    const std::vector<RigidBody*>& get_objects() const;

    void set_gravity(const Vector3& gravity);
    void step(double dt);
};