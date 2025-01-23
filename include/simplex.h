/**
 * @file simplex.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The Simplex2 struct represents a 2D simplex
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "vector.h"
#include "polygon.h"
#include <array>
#include <initializer_list>

namespace Physics
{
    /**
     * @brief The CSOSupport struct represents the support point of a Minkowski difference/configuration space object (CSO), along with the two support points from the original polygons
     * 
     */
    struct CSOSupport
    {
        Vector2 a; /**< Original support point of polygon A */
        Vector2 b; /**< Original support point of polygon B */
        Vector2 c; /**< Support point in the Minkowski difference */
        
        /**
         * @brief Construct a new CSOSupport object
         * 
         */
        CSOSupport();

        /**
         * @brief Construct a new CSOSupport object
         * 
         * @param a_poly 
         * @param b_poly 
         * @param d Direction to search for the support point
         */
        CSOSupport(const Polygon* const a_poly, const Polygon* const b_poly, Vector2 d);
    };

    /**
     * @brief The Simplex2 struct represents a 2D simplex
     * 
     */
    struct Simplex2
    {
    private:
        std::array<CSOSupport, 3> m_points;
        unsigned m_size;
        bool m_contains_origin;
    public:
        /**
         * @brief Construct a new Simplex2 object
         * 
         */
        Simplex2();

        /**
         * @brief Assign points to the simplex
         * 
         * @param points 
         * 
         * @return The simplex with the new points
         */
        Simplex2& operator=(std::initializer_list<CSOSupport> points);

        /**
         * @brief Add a point to the front of the array of points in the simplex
         * 
         * @param point 
         */
        void push_front(CSOSupport point);

        /**
         * @brief Get the point at index i
         * 
         * @param i 
         * 
         * @return The point
         */
        CSOSupport& operator[](unsigned i);
        
        /**
         * @brief Get the size of the simplex
         * 
         * @return The size
         */
        unsigned size() const;

        /**
         * @brief Set the flag indicating that the simplex contains the origin
         * 
         */
        void set_contains_origin();

        /**
         * @brief Check if the simplex contains the origin
         * 
         * If the simplex contains the origin, the two polygons are overlapping.
         * 
         * @return True if the simplex contains the origin
         */
        bool contains_origin() const;
    };
}