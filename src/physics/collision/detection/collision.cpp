#include "collision.h"

Collision::Collision(CollisionBody* a, CollisionBody* b, Contact contact)
    : a(a),
      b(b),
      contact(contact)
{
}