#include "bruteforce.h"
#include "simplex.h"
#include "gjk.h"
#include "epa.h"

void Bruteforce::update() {}
void Bruteforce::insert(CollisionBody* body) {};
void Bruteforce::remove(CollisionBody* body) {};

std::vector<Collision> Bruteforce::query(CollisionBody* body) const
{
    std::vector<Collision> collisions;

    for (CollisionBody* other : *m_objects) {
        if (body == other) continue;
        
        Simplex2 simplex = GJK(body->get_polygon(), other->get_polygon());
        
        if (simplex.contains_origin() ) {
            Contact contact = EPA(simplex, body->get_polygon(), other->get_polygon());
            collisions.emplace_back(body, other, contact);
        }
    }
    
    return collisions;
}

std::vector<Collision> Bruteforce::get_collisions() const
{
    std::vector<Collision> collisions;

    for (CollisionBody* const a : *m_objects) {
        for (CollisionBody* const b : *m_objects) {
            if (a == b) break;
            
            Simplex2 simplex = GJK(a->get_polygon(), b->get_polygon());
            
            if (simplex.contains_origin() ) {
                Contact contact = EPA(simplex, a->get_polygon(), b->get_polygon());
                collisions.emplace_back(a, b, contact);
            }
        }
    }
    
    return collisions;
}