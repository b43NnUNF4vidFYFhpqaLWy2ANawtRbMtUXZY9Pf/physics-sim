#pragma once

#include "rigid_body.h"
#include "contact.h"

struct Collision
{
    Collision(RigidBody* a, RigidBody* b, Contact contact);

    RigidBody* a;
    RigidBody* b;
    Contact contact;
};