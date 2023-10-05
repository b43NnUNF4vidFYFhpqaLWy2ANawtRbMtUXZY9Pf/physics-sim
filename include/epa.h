#pragma once

#include "contact.h"
#include "simplex.h"

namespace Physics::Collision::Detection::Narrowphase
{
    Physics::Collision::Detection::Narrowphase::Contact EPA(Simplex2& simplex, const Physics::Math::Polygon& a, const Physics::Math::Polygon& b);
}