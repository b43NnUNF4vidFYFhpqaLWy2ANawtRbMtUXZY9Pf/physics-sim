#include "collision.h"


namespace Physics
{
  CollisionPair::CollisionPair(CollisionBody* a, CollisionBody* b, Contact contact)
      : a(a),
        b(b),
        contact(contact)
  {}
}