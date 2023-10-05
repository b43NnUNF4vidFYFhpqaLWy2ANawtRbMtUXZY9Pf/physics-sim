#pragma once

#include "constraint.h"
#include "rigid_body.h"

namespace Physics::Collision::Resolution::Constraints
{
    class PlaneConstraint : public Constraint
    {
    private:
        Physics::Dynamics::RigidBody* rigid_body;
        const Physics::Math::Vector2 r;
        const Physics::Math::Vector2& n, t;
        float d;

        float inv_mass, inv_inertia, c_f;
        Physics::Math::Vector2 tau_norm, tau_tan;
        float m_eff, m_eff_t;
        float b;
        
        float m_total_lambda, m_total_lambda_t;
    public:
        PlaneConstraint(Physics::Dynamics::RigidBody* rigid_body, const Physics::Math::Vector2& p, const Physics::Math::Vector2& n, const Physics::Math::Vector2& t, float d, float beta);
        void solve() override;
    };
}