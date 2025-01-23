/**
 * @file vector.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The Vector2 struct represents a 3D vector
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

namespace Physics
{
    /**
     * @brief The Vector2 struct represents a 3D vector
     * 
     * @note Despite its 2D name, the z component is used for specific computations.
     */
    struct Vector2
    {
        float x; /**< x component */
        float y; /**< y component */
        float z; /**< z component */

        /**
         * @brief Construct a new Vector2 object
         * 
         * Initializes to (0, 0, 0)
         */
        Vector2();
        
        /**
         * @brief Construct a new Vector2 object with x and y components
         * 
         * Initializes z to 0
         * 
         * @param x
         * @param y 
         */
        Vector2(float x, float y);

        /**
         * @brief Construct a new Vector2 object with x, y, and z components
         * 
         * @param x
         * @param y
         * @param z 
         */
        Vector2(float x, float y, float z);
        
        /**
         * @brief Add two vectors component-wise
         * 
         * @param other
         * @return The sum of the two vectors
         */
        Vector2 operator+(const Vector2& other) const;

        /**
         * @brief Add vector to this vector component-wise
         * 
         * @param other 
         * @return The sum of the two vectors
         */
        Vector2& operator+=(const Vector2& other);

        /**
         * @brief Subtract two vectors component-wise
         * 
         * @param other 
         * @return The difference of the two vectors
         */
        Vector2 operator-(const Vector2& other) const;

        /**
         * @brief Divide this vector by a scalar
         * 
         * @param divisor 
         * @return The divided vector
         */
        Vector2 operator/(float divisor) const;

        /**
         * @brief Multiply this vector by a scalar
         * 
         * @param scalar 
         * @return The multiplied vector
         */
        Vector2 operator*(float scalar) const;
        
        /**
         * @brief Multiply this vector by a scalar
         * 
         * @param scalar 
         * @return The multiplied vector
         */
        Vector2& operator*=(float scalar);
        
        /**
         * @brief Multiply a vector by a scalar
         * 
         * This allows for left multiplication of a vector by a scalar.
         * 
         * @param scalar 
         * @param v 
         * @return The multiplied vector
         */
        friend Vector2 operator*(float scalar, const Vector2& v);

        /**
         * @brief Compute the dot product of two vectors
         * 
         * @param other 
         * @return The dot product
         */
        float dot(const Vector2& other) const;
        
        /**
         * @brief Compute the cross product of two vectors
         * 
         * @param other 
         * @return The cross product
         */
        Vector2 cross(const Vector2& other) const;
        
        /**
         * @brief Compute the magnitude/length of the vector
         * 
         * @return The magnitude
         */
        float mag();
        
        /**
         * @brief Compute the normalized/unit vector (magnitude = 1)
         * 
         * @return The normalized vector
         */
        Vector2 norm();
    };
}