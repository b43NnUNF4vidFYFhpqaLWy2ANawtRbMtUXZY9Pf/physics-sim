#pragma once

#include "constraint.h"
#include "collision.h"
#include "rigid_body.h"

namespace Physics::Collision::Resolution::Constraints
{
    class ContactConstraint : public Constraint
    {
    private:
        Physics::Dynamics::RigidBody* A;
        Physics::Dynamics::RigidBody* B;
        float d;
        float dt;

        Physics::Math::Vector2 r_a, r_b;
        Physics::Math::Vector2 n, t;
        Physics::Math::Vector2 j_va, j_wa, j_vb, j_wb;
        Physics::Math::Vector2 j_va_t, j_wa_t, j_vb_t, j_wb_t;
        float a_inv_mass, b_inv_mass, a_inv_inertia, b_inv_inertia;
        float m_eff, m_eff_t;
        float c_r, c_f;
        
        float m_total_lambda, m_total_lambda_t;
    public:
        ContactConstraint(Physics::Dynamics::RigidBody* A, Physics::Dynamics::RigidBody* B, Physics::Collision::Detection::Narrowphase::Contact& contact, float beta, float dt);
        void solve() override;
    };
}