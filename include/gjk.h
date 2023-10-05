#pragma once

#include "simplex.h"
#include "polygon.h"

namespace Physics::Collision::Detection::Narrowphase
{
    Simplex2 GJK(const Physics::Math::Polygon& a, const Physics::Math::Polygon& b);
    bool update_simplex(Simplex2& supports, Physics::Math::Vector2& directions);
    bool line_case(Simplex2& supports, Physics::Math::Vector2& direction);
    bool triangle_case(Simplex2& supports, Physics::Math::Vector2& direction);
}