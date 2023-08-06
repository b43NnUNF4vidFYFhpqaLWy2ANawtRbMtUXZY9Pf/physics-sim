#pragma once

#include "rigid_body.h"
#include "collision_solver.h"
#include <vector>
#include <cstddef>

class World
{
private:
    std::vector<RigidBody*> m_objects;
    std::vector<CollisionSolver*> m_solvers;

    Vector2 m_gravity;
    Vector2 m_gravity_point;
    float m_gravity_mag;
public:
    World();

    void reserve_objects(std::size_t cap);
    void add_object(RigidBody* object);
    void remove_object(RigidBody* object);
    const std::vector<RigidBody*>& get_objects() const;

    void reserve_solvers(std::size_t cap);
    void add_solver(CollisionSolver* solver);
    void remove_solver(CollisionSolver* solver);

    void set_gravity(const Vector2& gravity);
    void set_gravity_point(const Vector2& point, float mag);

    void solve_collisions(float dt);
    void step(float dt);
};