/**
 * @file epa.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The Expanding Polytope Algorithm (EPA) is used to generate contact data
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "contact.h"
#include "simplex.h"

namespace Physics
{
    /**
     * @brief Generate contact data using the Expanding Polytope Algorithm (EPA)
     * 
     * @param simplex The simplex produced by GJK
     * @param a The first polygon
     * @param b The second polygon
     * @return The contact data
     */
    Contact EPA(Simplex2& simplex, const Polygon* const a, const Polygon* const b);
}