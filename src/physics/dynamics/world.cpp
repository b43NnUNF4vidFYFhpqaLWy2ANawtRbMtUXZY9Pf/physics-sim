#include <algorithm>
#include <cstddef>
#include "world.h"
#include "vector.h"
#include "rigid_body.h"
#include "collision.h"
#include "gjk.h"
#include "epa.h"

World::World() {};

void World::reserve_objects(std::size_t cap)
{
    m_objects.reserve(cap);
}

void World::add_object(CollisionBody* object)
{
    m_objects.push_back(object);
}

void World::remove_object(CollisionBody* object)
{
    if (!object) return;
    
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

void World::set_gravity(const Vector2& gravity)
{
    m_gravity = gravity;
}

void World::set_gravity_point(const Vector2& point, float mag)
{
    m_gravity_point = point;
    m_gravity_mag = mag;
}

void World::solve_collisions(float dt)
{
    std::vector<Collision> collisions;
    
    // TODO: https://box2d.org/files/ErinCatto_DynamicBVH_Full.pdf
    for (CollisionBody* a : m_objects) {
        for (CollisionBody* b : m_objects) {
            if (a == b) break;
            
            Simplex2 simplex = GJK(a->get_polygon(), b->get_polygon());
            
            if (simplex.contains_origin() ) {
                Contact contact = EPA(simplex, a->get_polygon(), b->get_polygon());
                collisions.emplace_back(a, b, contact);
            }
        }
    }
    
    for (CollisionSolver* solver : m_solvers) {
        solver->solve(collisions, dt);
    }
}

void World::step(float dt)
{
    for (CollisionBody* object : m_objects) {
        RigidBody* rigid_body = dynamic_cast<RigidBody*>(object);

        if (rigid_body) {
            float m = rigid_body->get_mass();
            Vector2 c = rigid_body->get_polygon().get_centroid();
            Vector2 f_g = (m_gravity_point - c).norm()*m_gravity_mag*m;

            rigid_body->apply_force(m*m_gravity, c);
            rigid_body->apply_force(f_g, c);

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