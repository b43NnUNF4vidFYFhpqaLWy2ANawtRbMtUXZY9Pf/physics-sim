/**
 * @file plane_constraint.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The PlaneConstraint class represents a plane constraint
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "constraint.h"
#include "rigid_body.h"

namespace Physics
{
    /**
     * @brief The PlaneConstraint class enforces the separation of a rigid body from a (fixed) plane
     * 
     */
    class PlaneConstraint : public Constraint
    {
    private:
        RigidBody* rigid_body;
        const Vector2 r;
        const Vector2 n, t;
        float d;

        float inv_mass, inv_inertia, c_f;
        Vector2 tau_norm, tau_tan;
        float m_eff, m_eff_t;
        float b;
        
        float m_total_lambda, m_total_lambda_t;
    public:
        /**
         * @brief Construct a new Plane Constraint object
         * 
         * @param rigid_body The rigid body
         * @param p The contact point
         * @param n The contact normal pointing from plane to rigid body
         * @param t The contact tangent
         * @param d The penetration depth
         * @param beta The Baumgarte stabilization factor
         * 
         * @see Constraint for more information on the Baumgarte stabilization factor
         */
        PlaneConstraint(RigidBody* rigid_body, const Vector2& p, const Vector2& n, const Vector2& t, float d, float beta);
        void solve() override;
    };
}
