#pragma once

#include "vector.h"

namespace Physics::Collision::Detection::Narrowphase
{
    struct Contact
    {
        float penetrationDepth;
        Physics::Math::Vector2 a, b;
        Physics::Math::Vector2 normal;
        Physics::Math::Vector2 tangent;
    };
}