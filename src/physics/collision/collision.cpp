#include "collision.h"


namespace Physics::Collision
{
  CollisionPair::CollisionPair(Physics::Dynamics::CollisionBody* a, Physics::Dynamics::CollisionBody* b, Physics::Collision::Detection::Narrowphase::Contact contact)
      : a(a),
        b(b),
        contact(contact)
  {}
}