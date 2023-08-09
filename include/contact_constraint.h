#pragma once

#include "constraint.h"
#include "collision.h"
#include "rigid_body.h"

class ContactConstraint : public Constraint
{
private:
    RigidBody* A;
    RigidBody* B;
    float d;
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
    ContactConstraint(RigidBody* A, RigidBody* B, Contact& contact, float beta, float dt);
    void solve() override;
};