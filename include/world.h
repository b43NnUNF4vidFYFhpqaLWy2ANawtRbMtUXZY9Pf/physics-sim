#pragma once
#include "rigid_body.h"
#include <vector>
#include <cstddef>

class World
{
private:
    std::vector<RigidBody*> m_objects;
public:
    World();
    void reserve(std::size_t cap);
    void add_object(RigidBody* object);
    void remove_object(RigidBody* object);
    void step(float dt);
};