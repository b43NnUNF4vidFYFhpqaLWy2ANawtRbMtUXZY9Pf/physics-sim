#pragma once

#include "rigid_body.h"
#include "collision_solver.h"
#include "collision_detector.h"
#include <vector>
#include <cstddef>

namespace Physics
{
    class World
    {
    private:
        std::vector<Physics::Dynamics::CollisionBody*> m_objects;
        std::vector<Physics::Collision::Resolution::Constraints::CollisionSolver*> m_solvers;

        Physics::Math::Vector2 m_gravity;

        void solve_collisions(float dt);
    public:
        Physics::Collision::Detection::CollisionDetector* m_collision_detector;

        World() = default;
        void set_collision_detector(Physics::Collision::Detection::CollisionDetector* collision_detector);

        void reserve_objects(std::size_t cap);
        void add_object(Physics::Dynamics::CollisionBody* object);
        void remove_object(Physics::Dynamics::CollisionBody* object);
        const std::vector<Physics::Dynamics::CollisionBody*>& get_objects() const;

        void reserve_solvers(std::size_t cap);
        void add_solver(Physics::Collision::Resolution::Constraints::CollisionSolver* solver);
        void remove_solver(Physics::Collision::Resolution::Constraints::CollisionSolver* solver);

        void set_gravity(const Physics::Math::Vector2& gravity);
        
        void step(float dt);
    };
}