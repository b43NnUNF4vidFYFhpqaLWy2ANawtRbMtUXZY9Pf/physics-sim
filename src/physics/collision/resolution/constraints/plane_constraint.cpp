#include "plane_constraint.h"

PlaneConstraint::PlaneConstraint(RigidBody* rigid_body, const Vector2& p, const Vector2& n, float d, float beta)
    : Constraint(beta),
      rigid_body(rigid_body),
      r(p - rigid_body->get_polygon().get_centroid()),
      n(n),
      d(d),
      inv_mass(rigid_body->get_invMass()),
      inv_inertia(rigid_body->get_invInertia()),
      tau_norm(r.cross(n)),
      m_eff( 1/(inv_mass + inv_inertia*(tau_norm.dot(tau_norm))) )
{}

void PlaneConstraint::solve()
{
    Vector2 v = rigid_body->get_vel();
    Vector2 omega = {0, 0, rigid_body->get_angVel()};
    Vector2 C_t = v + omega.cross(r);

    float b = -beta*d;
    float lambda = -m_eff*(C_t.dot(n) + b);
    
    rigid_body->add_vel(inv_mass*n*lambda);
    rigid_body->add_angVel( (inv_inertia*tau_norm*lambda).z );
}