#include "collision.h"

Collision::Collision(RigidBody* a, RigidBody* b, Contact contact)
    : a(a),
      b(b),
      contact(contact)
{
}