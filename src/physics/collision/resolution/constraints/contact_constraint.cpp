#include "contact_constraint.h"
#include <algorithm>

ContactConstraint::ContactConstraint(RigidBody* A, RigidBody* B, Contact& contact, float beta, float dt) 
    : Constraint(beta, dt),
      A(A),
      B(B),
      contact(contact),

      r_a(contact.a - A->get_polygon().get_centroid()),
      r_b(contact.b - B->get_polygon().get_centroid()),
      n(contact.normal),

      j_va(-1*n),
      j_wa(-1*r_a.cross(n)),
      j_vb(n),
      j_wb(r_b.cross(n)),

      a_inv_mass(A->get_invMass()),
      b_inv_mass(B->get_invMass()),
      a_inv_inertia(A->get_invInertia()),
      b_inv_inertia(B->get_invInertia()),

      m_eff( 1/(a_inv_mass + j_wa.dot(a_inv_inertia*j_wa) + b_inv_mass + j_wb.dot(b_inv_inertia*j_wb)) ),
      c_r(A->get_restitution()*B->get_restitution())
{
}

void ContactConstraint::solve()
{
    Vector2 a_vel = A->get_vel();
    Vector2 a_angVel = {0, 0, A->get_angVel()};
    Vector2 b_vel = B->get_vel();
    Vector2 b_angVel = {0, 0, B->get_angVel()};

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
    float b = -(beta/dt)*contact.penetrationDepth + c_r*closing_vel;

    float lambda = m_eff*(-(jv + b));
    float old_total_lambda = m_total_lambda;
    m_total_lambda = std::max(0.0f, m_total_lambda + lambda);
    lambda = m_total_lambda - old_total_lambda;

    A->add_vel(a_inv_mass*j_va*lambda);
    A->add_angVel((a_inv_inertia*j_wa*lambda).z);
    B->add_vel(b_inv_mass*j_vb*lambda);
    B->add_angVel((b_inv_inertia*j_wb*lambda).z);
}