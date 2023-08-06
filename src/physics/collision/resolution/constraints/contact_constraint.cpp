#include "contact_constraint.h"
#include <algorithm>

// TODO: Find out how to deal with static body to rigid body collision
ContactConstraint::ContactConstraint(Collision& collision, float beta, float dt) 
    : Constraint(beta, dt),
      collision(collision),

      r_a(collision.contact.a - collision.a->get_polygon().get_centroid()),
      r_b(collision.contact.b - collision.b->get_polygon().get_centroid()),
      n(collision.contact.normal),

      j_va(-1*n),
      j_wa(-1*r_a.cross(n)),
      j_vb(n),
      j_wb(r_b.cross(n)),

      a_inv_mass(collision.a->get_invMass()),
      b_inv_mass(collision.b->get_invMass()),
      a_inv_inertia(collision.a->get_invInertia()),
      b_inv_inertia(collision.b->get_invInertia()),

      m_eff( 1/(a_inv_mass + j_wa.dot(a_inv_inertia*j_wa) + b_inv_mass + j_wb.dot(b_inv_inertia*j_wb)) ),
      c_r(collision.a->get_restitution()*collision.b->get_restitution())
{
}

void ContactConstraint::solve()
{
    Vector2 a_vel = collision.a->get_vel();
    Vector2 a_angVel = {0, 0, collision.a->get_angVel()};
    Vector2 b_vel = collision.b->get_vel();
    Vector2 b_angVel = {0, 0, collision.b->get_angVel()};

    float jv =
        j_va.dot(a_vel)
      + j_wa.dot(a_angVel)
      + j_vb.dot(b_vel)
      + j_wb.dot(b_angVel);

    Vector2 relative_vel =
      -1*a_vel
      - a_angVel.cross(r_a)
      + b_vel
      + b_angVel.cross(r_b);
    float closing_vel = n.dot(relative_vel);
    float b = -(beta/dt)*collision.contact.penetrationDepth + c_r*closing_vel;

    float lambda = m_eff*(-(jv + b));
    float old_total_lambda = m_total_lambda;
    m_total_lambda = std::max(0.0f, m_total_lambda + lambda);
    lambda = m_total_lambda - old_total_lambda;

    collision.a->add_vel(a_inv_mass*j_va*lambda);
    collision.a->add_angVel((a_inv_inertia*j_wa*lambda).z);
    collision.b->add_vel(b_inv_mass*j_vb*lambda);
    collision.b->add_angVel((b_inv_inertia*j_wb*lambda).z);
}