#include <algorithm>
#include "world.h"
#include "vector.h"
#include "rigid_body.h"
#include "collision.h"

namespace Physics
{
    void World::set_collision_detector(Physics::Collision::Detection::CollisionDetector* collision_detector)
    {
        m_collision_detector = collision_detector;
        m_collision_detector->set_objects(&m_objects);
    }

    void World::reserve_objects(std::size_t cap)
    {
        m_objects.reserve(cap);
    }

    void World::add_object(Physics::Dynamics::CollisionBody* object)
    {
        m_objects.push_back(object);
        m_collision_detector->insert(object);
    }

    void World::remove_object(Physics::Dynamics::CollisionBody* object)
    {
        if (!object) return;
        
        m_collision_detector->remove(object);

        auto itr = std::find(m_objects.begin(), m_objects.end(), object);
        if ( itr == m_objects.end() ) return;
        m_objects.erase(itr);
    }

    const std::vector<Physics::Dynamics::CollisionBody*>& World::get_objects() const
    {
        return m_objects;
    }

    void World::reserve_solvers(std::size_t cap)
    {
        m_solvers.reserve(cap);
    }

    void World::add_solver(Physics::Collision::Resolution::Constraints::CollisionSolver* solver)
    {
        m_solvers.push_back(solver);
    }

    void World::remove_solver(Physics::Collision::Resolution::Constraints::CollisionSolver* solver)
    {
        if (!solver) return;
        
        auto itr = std::find(m_solvers.begin(), m_solvers.end(), solver);
        if ( itr == m_solvers.end() ) return;
        
        m_solvers.erase(itr);
    }

    void World::solve_collisions(float dt)
    {
        m_collision_detector->update();
        std::vector<Physics::Collision::CollisionPair> collisions = m_collision_detector->get_collisions();

        for (Physics::Collision::Resolution::Constraints::CollisionSolver* solver : m_solvers) {
            solver->solve(collisions, dt);
        }
    }

    void World::set_gravity(const Physics::Math::Vector2& gravity)
    {
        m_gravity = gravity;
    }

    void World::step(float dt)
    {
        for (Physics::Dynamics::CollisionBody* object : m_objects) {
            Physics::Dynamics::RigidBody* rigid_body = dynamic_cast<Physics::Dynamics::RigidBody*>(object);

            if (rigid_body) {
                rigid_body->apply_force(rigid_body->get_mass()*m_gravity, rigid_body->get_polygon().get_centroid());
                rigid_body->update_vel(dt);
            }
        }
        
        solve_collisions(dt);

        for (Physics::Dynamics::CollisionBody* object : m_objects) {
            Physics::Dynamics::RigidBody* rigid_body = dynamic_cast<Physics::Dynamics::RigidBody*>(object);

            if (rigid_body) {
                rigid_body->update_pos(dt);
            }
        }
    }
}