#pragma once

#include "constraint.h"
#include "rigid_body.h"

class PlaneConstraint : public Constraint
{
private:
    RigidBody* rigid_body;
    const Vector2 r;
    const Vector2& n, t;
    float d;

    float inv_mass, inv_inertia, c_f;
    Vector2 tau_norm, tau_tan;
    float m_eff, m_eff_t;
    float b;
    
    float m_total_lambda, m_total_lambda_t;
public:
    PlaneConstraint(RigidBody* rigid_body, const Vector2& p, const Vector2& n, const Vector2& t, float d, float beta);
    void solve() override;
};