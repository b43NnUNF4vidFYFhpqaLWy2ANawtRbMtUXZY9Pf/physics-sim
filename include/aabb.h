/**
 * @file aabb.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The AABB class represents an axis-aligned bounding box.
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
    class Polygon;

    /**
     * @brief The AABB class represents an axis-aligned bounding box.
     * 
     * An AABB is a box that is aligned with the x and y axes and contains a polygon.
     */
    struct AABB
    {
        Vector2 min; /**< The point with the smallest x and y values */
        Vector2 max; /**< The point with the largest x and y values */
        
        AABB() = default;
        
        /**
         * @brief Construct a new AABB object from a polygon
         * 
         * @param polygon
         */
        AABB(const Polygon* const polygon);

        /**
         * @brief Check if this AABB collides with another AABB
         * 
         * @param other
         * 
         * @return True if the AABBs collide
         * 
         * @note If two AABBs collide, then their polygons *may* collide and must be checked by a narrowphase algorithm.
         */
        bool collides(const AABB& other) const;

        /**
         * @brief Check if this AABB contains another AABB inside itself
         * 
         * @param other
         * 
         * @return True if this AABB contains the other AABB
         */
        bool contains(const AABB& other) const;

        /**
         * @brief Get the union of this AABB and another AABB
         * 
         * The union is the smallest AABB that contains both AABBs.
         * 
         * @param other
         * 
         * @return The union of the two AABBs
         */
        AABB Union(AABB* other) const;

        /**
         * @brief Get the area of the AABB
         * 
         * @return The area
         */
        float area() const;
    };
}
