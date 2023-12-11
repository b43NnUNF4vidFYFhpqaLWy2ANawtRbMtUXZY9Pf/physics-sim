#pragma once

#include "collision_body.h"
#include "contact.h"

namespace Physics
{
    struct CollisionPair
    {
        CollisionPair(CollisionBody* a, CollisionBody* b, Contact contact);

        CollisionBody* a;
        CollisionBody* b;
        Contact contact;
    };
}