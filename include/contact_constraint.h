#pragma once

#include "constraint.h"
#include "collision.h"
#include "rigid_body.h"

class ContactConstraint : public Constraint
{
private:
    RigidBody* A;
    RigidBody* B;
    Contact& contact;
    float dt;

    Vector2 r_a, r_b;
    Vector2 n;
    Vector2 j_va, j_wa, j_vb, j_wb;
    float a_inv_mass, b_inv_mass, a_inv_inertia, b_inv_inertia;
    float m_eff;
    float c_r;
public:
    ContactConstraint(RigidBody* A, RigidBody* B, Contact& contact, float beta, float dt);
    void solve() override;
};