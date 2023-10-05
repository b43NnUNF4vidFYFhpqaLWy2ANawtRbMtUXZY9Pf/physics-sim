#include "plane_constraint.h"
#include <algorithm>

namespace Physics::Collision::Resolution::Constraints
{
    PlaneConstraint::PlaneConstraint(Physics::Dynamics::RigidBody* rigid_body, const Physics::Math::Vector2& p, const Physics::Math::Vector2& n, const Physics::Math::Vector2& t, float d, float beta)
        : Constraint(beta),
          rigid_body(rigid_body),
          r(p - rigid_body->get_polygon().get_centroid()),
          n(n),
          t(t),
          d(d),

          inv_mass(rigid_body->get_invMass()),
          inv_inertia(rigid_body->get_invInertia()),
          c_f(rigid_body->get_friction()),
          tau_norm(r.cross(n)),
          tau_tan(r.cross(t)),
          m_eff( 1/(inv_mass + inv_inertia*(tau_norm.dot(tau_norm))) ),
          m_eff_t( 1/(inv_mass + inv_inertia*(tau_tan.dot(tau_tan))) ),
          b(-beta*d),

          m_total_lambda(0),
          m_total_lambda_t(0)
    {}

    void PlaneConstraint::solve()
    {
        Physics::Math::Vector2 v = rigid_body->get_vel();
        Physics::Math::Vector2 omega = {0, 0, rigid_body->get_angVel()};
        Physics::Math::Vector2 C_t = v + omega.cross(r);

        float lambda = -m_eff*(C_t.dot(n) + b);
        float old_total_lambda = m_total_lambda;
        m_total_lambda = std::max(0.0f, m_total_lambda + lambda);
        lambda = m_total_lambda - old_total_lambda;
        
        rigid_body->add_vel(inv_mass*n*lambda);
        rigid_body->add_angVel( (inv_inertia*tau_norm*lambda).z );
        
        float lambda_t = -m_eff_t*(C_t.dot(t));
        float old_total_lambda_t = m_total_lambda_t;
        m_total_lambda_t = std::clamp(m_total_lambda_t + lambda_t, -c_f*m_total_lambda, c_f*m_total_lambda);
        lambda_t = m_total_lambda_t - old_total_lambda_t;

        rigid_body->add_vel(inv_mass*t*lambda_t);
        rigid_body->add_angVel( (inv_inertia*tau_tan*lambda_t).z );
    }
}