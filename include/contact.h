/**
 * @file contact.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The Contact struct holds data about a collision
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "vector.h"

namespace Physics
{
    /**
     * @brief The Contact struct holds data about a collision
     * 
     */
    struct Contact
    {
        float penetrationDepth; /**< The depth of the overlap between the polygons */
        Vector2 a; /**< The contact point on polygon A such that it is the deepest penetrating point of A inside B */
        Vector2 b; /**< The contact point on polygon B such that it is the deepest penetrating point of B inside A */

        /**
         * @brief The contact normal is the direction of the collision such that it is the "best direction" to separate the two polygons
         * 
         * @note The contact normal is always pointing from A to B
         */
        Vector2 normal;
        Vector2 tangent; /**< The contact tangent (perpendicular to the contact normal) */
    };
}