#include "bruteforce.h"
#include "simplex.h"
#include "gjk.h"
#include "epa.h"

namespace Physics::Collision::Detection::Broadphase::Bruteforce
{
    void Bruteforce::update() {}
    void Bruteforce::insert(Physics::Dynamics::CollisionBody* body) {};
    void Bruteforce::remove(Physics::Dynamics::CollisionBody* body) {};

    std::vector<Physics::Collision::CollisionPair> Bruteforce::query(Physics::Dynamics::CollisionBody* body) const
    {
        std::vector<Physics::Collision::CollisionPair> collisions;

        for (Physics::Dynamics::CollisionBody* other : *m_objects) {
            if (body == other) continue;
            
            Physics::Collision::Detection::Narrowphase::Simplex2 simplex = Physics::Collision::Detection::Narrowphase::GJK(body->get_polygon(), other->get_polygon());
            
            if (simplex.contains_origin() ) {
                Physics::Collision::Detection::Narrowphase::Contact contact = Physics::Collision::Detection::Narrowphase::EPA(simplex, body->get_polygon(), other->get_polygon());
                collisions.emplace_back(body, other, contact);
            }
        }
        
        return collisions;
    }

    std::vector<Physics::Collision::CollisionPair> Bruteforce::get_collisions() const
    {
        std::vector<Physics::Collision::CollisionPair> collisions;

        for (Physics::Dynamics::CollisionBody* const a : *m_objects) {
            for (Physics::Dynamics::CollisionBody* const b : *m_objects) {
                if (a == b) break;
                
                Physics::Collision::Detection::Narrowphase::Simplex2 simplex = Physics::Collision::Detection::Narrowphase::GJK(a->get_polygon(), b->get_polygon());
                
                if (simplex.contains_origin() ) {
                    Physics::Collision::Detection::Narrowphase::Contact contact = Physics::Collision::Detection::Narrowphase::EPA(simplex, a->get_polygon(), b->get_polygon());
                    collisions.emplace_back(a, b, contact);
                }
            }
        }
        
        return collisions;
    }
}