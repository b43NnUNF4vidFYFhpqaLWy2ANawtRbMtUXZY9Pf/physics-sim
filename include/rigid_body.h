/**
 * @file rigid_body.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The RigidBody class represents a polygon with collision detection and dynamics capabilities.
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "collision_body.h"
#include "vector.h"

namespace Physics
{
    /**
     * @brief The RigidBody class represents a polygon with collision detection and dynamics capabilities.
     * 
     */
    class RigidBody : public CollisionBody
    {
    private:
        Vector2 m_vel;
        Vector2 m_force;
        float m_angularVelocity;
        float m_torque;
        
        float m_mass;
        float m_invMass;
        float m_inertia;
        float m_invInertia;
        
        float m_restitution;
        float m_friction;

        void calc_moment_of_inertia();
    public:
        /**
         * @brief Construct a new RigidBody object
         * 
         * @param vertices The vertices of the polygon
         * @param mass The mass of the object
         * @param restitution The coefficient of restitution
         * @param friction The coefficient of friction
         * 
         * @pre The vertices should be in counter-clockwise order and the polygon should be convex (use is_convex() to check)
         */
        RigidBody(std::vector<Vector2> vertices, float mass, float restitution, float friction);

        /**
         * @brief Get the velocity
         * 
         * @return The velocity
         */
        Vector2 get_vel() const;

        /**
         * @brief Get the angular velocity
         * 
         * @return The angular velocity
         */
        float get_angVel() const;
        
        /**
         * @brief Get the mass
         * 
         * @return The mass
         */
        float get_mass() const;

        /**
         * @brief Get the inverse mass
         * 
         * @return The inverse mass
         */
        float get_invMass() const;

        /**
         * @brief Get the inverse inertia
         * 
         * @return The inverse inertia
         */
        float get_invInertia() const;

        /**
         * @brief Get the coefficient of restitution
         * 
         * @return The coefficient of restitution
         */
        float get_restitution() const;

        /**
         * @brief Get the coefficient of friction
         * 
         * @return The coefficient of friction
         */
        float get_friction() const;
        
        /**
         * @brief Add velocity
         * 
         * @param v The velocity to add
         */
        void add_vel(const Vector2& v);

        /**
         * @brief Add angular velocity
         * 
         * @param a The angular velocity to add
         */
        void add_angVel(float a);

        /**
         * @brief Apply a force to the object
         * 
         * @note This only accumulates forces. To apply the forces, call update_vel(), then update_pos().
         * 
         * @param f The force to apply
         * @param p The point of application
         */
        void apply_force(const Vector2& f, const Vector2& p);

        /**
         * @brief Update the linear and angular velocity
         * 
         * @note This also resets the forces. This function should be called before update_pos().
         * 
         * @param dt The time step
         */
        void update_vel(float dt);

        /**
         * @brief Update the position and orientation
         * 
         * @param dt The time step
         */
        void update_pos(float dt);
    };
}
