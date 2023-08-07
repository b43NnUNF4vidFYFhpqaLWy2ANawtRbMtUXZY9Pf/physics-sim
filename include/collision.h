#pragma once

#include "collision_body.h"
#include "contact.h"

struct Collision
{
    Collision(CollisionBody* a, CollisionBody* b, Contact contact);

    CollisionBody* a;
    CollisionBody* b;
    Contact contact;
};