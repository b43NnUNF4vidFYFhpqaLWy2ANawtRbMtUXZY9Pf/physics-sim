/**
 * @file contact_constraint.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The ContactConstraint class represents a contact constraint
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
     * @brief The contact constraint enforces the separation of two colliding rigid bodies
     * 
     */
    class ContactConstraint : public Constraint
    {
    private:
        RigidBody* A;
        RigidBody* B;
        float d;
        float slop_p;
        float slop_r;
        float dt;

        Vector2 r_a, r_b;
        Vector2 n, t;
        Vector2 j_va, j_wa, j_vb, j_wb;
        Vector2 j_va_t, j_wa_t, j_vb_t, j_wb_t;
        float a_inv_mass, b_inv_mass, a_inv_inertia, b_inv_inertia;
        float m_eff, m_eff_t;
        float c_r, c_f;
        
        float m_total_lambda, m_total_lambda_t;
    public:
        /**
         * @brief Construct a new ContactConstraint object
         * 
         * @param A The first rigid body
         * @param B The second rigid body
         * @param contact The contact data
         * @param beta The Baumgarte stabilization factor
         * @param slop_p The penetration slop: Amount of penetration allowed before Baumgarte stabilization is applied
         * @param slop_r The restitution slop: Amount of restitution allowed before Baumgarte stabilization is applied
         * @param dt The time step
         * 
         * @see Constraint for more information on the Baumgarte stabilization factor
         */
        ContactConstraint(RigidBody* A, RigidBody* B, Contact& contact, float beta, float slop_p, float slop_r, float dt);
        void solve() override;
    };
}
