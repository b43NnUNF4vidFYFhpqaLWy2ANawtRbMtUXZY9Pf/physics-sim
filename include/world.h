#pragma once
#include "rigid_body.h"
#include <vector>
#include <cstddef>

class World
{
private:
    std::vector<CollisionBody*> m_objects;
    Vector2 m_gravity;
public:
    World();

    void reserve_objects(std::size_t cap);
    void add_object(CollisionBody* object);
    void remove_object(CollisionBody* object);
    const std::vector<CollisionBody*>& get_objects() const;

    void set_gravity(const Vector2& gravity);
    void step(double dt);
};