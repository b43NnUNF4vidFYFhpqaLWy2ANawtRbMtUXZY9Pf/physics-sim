#pragma once

#include "collision_body.h"
#include "contact.h"

namespace Physics::Collision
{
    struct CollisionPair
    {
        CollisionPair(Physics::Dynamics::CollisionBody* a, Physics::Dynamics::CollisionBody* b, Physics::Collision::Detection::Narrowphase::Contact contact);

        Physics::Dynamics::CollisionBody* a;
        Physics::Dynamics::CollisionBody* b;
        Physics::Collision::Detection::Narrowphase::Contact contact;
    };
}