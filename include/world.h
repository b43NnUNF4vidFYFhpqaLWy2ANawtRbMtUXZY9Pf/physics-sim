#pragma once

#include "rigid_body.h"
#include "collision_solver.h"
#include "collision_detector.h"
#include <vector>
#include <cstddef>

class World
{
private:
    std::vector<CollisionBody*> m_objects;
    std::vector<CollisionSolver*> m_solvers;

    Vector2 m_gravity;

    void solve_collisions(float dt);
public:
    CollisionDetector* m_collision_detector;

    World() = default;
    void set_collision_detector(CollisionDetector* collision_detector);

    void reserve_objects(std::size_t cap);
    void add_object(CollisionBody* object);
    void remove_object(CollisionBody* object);
    const std::vector<CollisionBody*>& get_objects() const;

    void reserve_solvers(std::size_t cap);
    void add_solver(CollisionSolver* solver);
    void remove_solver(CollisionSolver* solver);

    void set_gravity(const Vector2& gravity);
    
    void step(float dt);
};