#pragma once

#include "constraint.h"
#include "rigid_body.h"

class PlaneConstraint : public Constraint
{
private:
    RigidBody* rigid_body;
    const Vector2 r;
    const Vector2& n;
    float d;
    float inv_mass;
    float inv_inertia;
    Vector2 tau_norm;
    float m_eff;
public:
    PlaneConstraint(RigidBody* rigid_body, const Vector2& p, const Vector2& n, float d, float beta);
    void solve() override;
};