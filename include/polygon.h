/**
 * @file polygon.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The Polygon class represents a convex polygon.
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "vector.h"
#include <vector>

namespace Physics
{
    /**
     * @brief The Polygon class represents a convex polygon.
     * 
     */
    class Polygon
    {
    private:
        std::vector<Vector2> m_vertices;
        Vector2 m_centroid;

        Vector2 find_centroid() const;
    public:
        /**
         * @brief Construct a new Polygon object
         * 
         * @param vertices The vertices of the polygon
         * 
         * @pre The vertices should be in counter-clockwise order and the polygon should be convex (use is_convex() to check)
         */
        Polygon(std::vector<Vector2> vertices);

        /**
         * @brief Generate a random polygon
         * 
         * @param r Radius of the polygon
         * @param at Center of the polygon
         * 
         * @return A random polygon
         */
        static Polygon gen_random(unsigned r, const Vector2& at);

        /**
         * @brief Move the polygon
         * 
         * @param delta The displacement
         */
        void move(const Vector2& delta);

        /**
         * @brief Rotate the polygon
         * 
         * @param v The angle in radians
         */
        void rotate(float v);

        /**
         * @brief Check if the polygon is convex
         * 
         * @return true if the polygon is convex
         */
        bool is_convex() const;
        
        /**
         * @brief Get the vertices of the polygon
         * 
         * @return The vertices of the polygon
         */
        const std::vector<Vector2>& get_vertices() const;

        /**
         * @brief Get the centroid of the polygon
         * 
         * @return The centroid of the polygon
         */
        const Vector2& get_centroid() const;

        /**
         * @brief Get the support point in a direction
         * 
         * @param d The direction
         * 
         * @return The support point
         */
        Vector2 support(Vector2 d) const;
    };
}
