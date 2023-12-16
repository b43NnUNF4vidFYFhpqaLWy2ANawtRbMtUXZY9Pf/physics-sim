#pragma once

#include "collision.h"
#include "collision_detector.h"
#include "collision_solver.h"
#include <cstddef>
#include <vector>

namespace Physics
{
    class World
    {
    private:
        CollisionDetector* m_collision_detector;
        std::vector<CollisionBody*> m_objects;
        std::vector<CollisionSolver*> m_solvers;
        Vector2 m_gravity;

        void solve_collisions(float dt);
        void send_collision_callbacks(std::vector<CollisionPair>& collisions, float dt);
    public:
        World();

        void set_collision_detector(CollisionDetector* collision_detector);
        CollisionDetector* get_collision_detector() const;

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
}
