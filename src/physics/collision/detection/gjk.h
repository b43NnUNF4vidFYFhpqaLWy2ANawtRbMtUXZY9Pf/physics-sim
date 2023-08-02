#pragma once

#include "simplex.h"
#include "polygon.h"

Simplex2 GJK(const Polygon& a, const Polygon& b);
bool update_simplex(Simplex2& supports, Vector2& directions);
bool line_case(Simplex2& supports, Vector2& direction);
bool triangle_case(Simplex2& supports, Vector2& direction);