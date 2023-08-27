#pragma once

#include "collision_body.h"
#include "collision.h"

class CollisionDetector
{
protected:
    std::vector<CollisionBody*>* m_objects;
public:
    void set_objects(std::vector<CollisionBody*>* objects);
    virtual void update() = 0;
    virtual void insert(CollisionBody* body) = 0;
    virtual void remove(CollisionBody* body) = 0;
    virtual std::vector<Collision> query(CollisionBody* const body) const = 0;
    virtual std::vector<Collision> get_collisions() const = 0;
};