#include "bruteforce.h"
#include "epa.h"
#include "gjk.h"
#include "simplex.h"

namespace Physics
{
    void Bruteforce::set_objects(std::vector<CollisionBody*>* objects)
    {
        m_objects = objects;
    }

    void Bruteforce::update() {}
    void Bruteforce::insert([[maybe_unused]] CollisionBody* body) {};
    void Bruteforce::remove([[maybe_unused]] CollisionBody* body) {};

    std::vector<CollisionPair>& Bruteforce::get_collisions()
    {
        m_collisions.clear();

        for (CollisionBody* const a : *m_objects) {
            for (CollisionBody* const b : *m_objects) {
                if (a == b) break;
                
                Simplex2 simplex = GJK(a, b);
                
                if (simplex.contains_origin() ) {
                    Contact contact = EPA(simplex, a, b);
                    m_collisions.emplace_back(a, b, contact);
                }
            }
        }
        
        m_collisions.shrink_to_fit();

        return m_collisions;
    }
}
