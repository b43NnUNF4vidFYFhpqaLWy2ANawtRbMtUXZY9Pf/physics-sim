#pragma once

#include "vector.h"

struct Contact
{
    float penetrationDepth;
    Vector2 normal;
    Vector2 tangent;
};