#include "world.h"
#include "collision.h"
#include "rigid_body.h"
#include "vector.h"
#include <algorithm>

namespace Physics
{
    World::World() : m_collision_detector(nullptr) {}

    void World::set_collision_detector(CollisionDetector* collision_detector)
    {
        m_collision_detector = collision_detector;
        m_collision_detector->set_objects(&m_objects);
    }

    CollisionDetector* World::get_collision_detector() const
    {
        return m_collision_detector;
    }

    void World::reserve_objects(std::size_t cap)
    {
        m_objects.reserve(cap);
    }

    void World::add_object(CollisionBody* object)
    {
        m_objects.push_back(object);
        if (m_collision_detector) m_collision_detector->insert(object);
    }

    void World::remove_object(CollisionBody* object)
    {
        if (!object) return;
        
        if (m_collision_detector) m_collision_detector->remove(object);

        auto itr = std::find(m_objects.begin(), m_objects.end(), object);
        if ( itr == m_objects.end() ) return;
        m_objects.erase(itr);
    }

    const std::vector<CollisionBody*>& World::get_objects() const
    {
        return m_objects;
    }

    void World::reserve_solvers(std::size_t cap)
    {
        m_solvers.reserve(cap);
    }

    void World::add_solver(CollisionSolver* solver)
    {
        m_solvers.push_back(solver);
    }

    void World::remove_solver(CollisionSolver* solver)
    {
        if (!solver) return;
        
        auto itr = std::find(m_solvers.begin(), m_solvers.end(), solver);
        if ( itr == m_solvers.end() ) return;
        
        m_solvers.erase(itr);
    }

    void World::solve_collisions(float dt)
    {
        if (!m_collision_detector) return;

        m_collision_detector->update();
        std::vector<CollisionPair> collisions = m_collision_detector->get_collisions();

        for (CollisionSolver* solver : m_solvers) {
            solver->solve(collisions, dt);
        }
    }

    void World::set_gravity(const Vector2& gravity)
    {
        m_gravity = gravity;
    }

    void World::step(float dt)
    {
        for (CollisionBody* object : m_objects) {
            RigidBody* rigid_body = dynamic_cast<RigidBody*>(object);

            if (rigid_body) {
                rigid_body->apply_force(rigid_body->get_mass()*m_gravity, rigid_body->get_centroid());
                rigid_body->update_vel(dt);
            }
        }
        
        solve_collisions(dt);

        for (CollisionBody* object : m_objects) {
            RigidBody* rigid_body = dynamic_cast<RigidBody*>(object);

            if (rigid_body) {
                rigid_body->update_pos(dt);
            }
        }
    }
}
