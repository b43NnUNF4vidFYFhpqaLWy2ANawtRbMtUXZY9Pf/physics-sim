#pragma once

#include "contact.h"

namespace Physics
{
    class CollisionBody;

    struct CollisionPair
    {
        CollisionPair(CollisionBody* a, CollisionBody* b, Contact contact);

        CollisionBody* a;
        CollisionBody* b;
        Contact contact;
    };
}
