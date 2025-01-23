/**
 * @file gjk.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The GJK algorithm is used to detect collisions between two polygons
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "simplex.h"
#include "polygon.h"

namespace Physics
{
    /**
     * @brief Perform the Gilbert-Johnson-Keerthi (GJK) algorithm in 2D to detect collisions between two polygons
     * 
     * @param a 
     * @param b 
     * 
     * @return The simplex found by GJK
     */
    Simplex2 GJK(const Polygon* const a, const Polygon* const b);
    bool update_simplex(Simplex2& supports, Vector2& directions);
    bool line_case(Simplex2& supports, Vector2& direction);
    bool triangle_case(Simplex2& supports, Vector2& direction);
}