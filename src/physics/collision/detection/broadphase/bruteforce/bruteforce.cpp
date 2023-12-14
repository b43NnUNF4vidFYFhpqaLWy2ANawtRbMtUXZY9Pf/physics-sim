#include "bruteforce.h"
#include "simplex.h"
#include "gjk.h"
#include "epa.h"

namespace Physics
{
    void Bruteforce::update() {}
    void Bruteforce::insert(CollisionBody* body) {};
    void Bruteforce::remove(CollisionBody* body) {};

    std::vector<CollisionPair> Bruteforce::query(CollisionBody* body) const
    {
        std::vector<CollisionPair> collisions;

        for (CollisionBody* other : *m_objects) {
            if (body == other) continue;
            
            Simplex2 simplex = GJK(body, other);
            
            if (simplex.contains_origin() ) {
                Contact contact = EPA(simplex, body, other);
                collisions.emplace_back(body, other, contact);
            }
        }
        
        return collisions;
    }

    std::vector<CollisionPair> Bruteforce::get_collisions() const
    {
        std::vector<CollisionPair> collisions;

        for (CollisionBody* const a : *m_objects) {
            for (CollisionBody* const b : *m_objects) {
                if (a == b) break;
                
                Simplex2 simplex = GJK(a, b);
                
                if (simplex.contains_origin() ) {
                    Contact contact = EPA(simplex, a, b);
                    collisions.emplace_back(a, b, contact);
                }
            }
        }
        
        return collisions;
    }
}