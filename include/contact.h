#pragma once

#include "vector.h"

namespace Physics
{
    struct Contact
    {
        float penetrationDepth;
        Vector2 a, b;
        Vector2 normal;
        Vector2 tangent;
    };
}