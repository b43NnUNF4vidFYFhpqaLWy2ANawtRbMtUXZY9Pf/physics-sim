#include "contact_constraint.h"
#include <algorithm>

ContactConstraint::ContactConstraint(RigidBody* A, RigidBody* B, Contact& contact, float beta, float dt) 
    : Constraint(beta),
      A(A),
      B(B),
      d(contact.penetrationDepth),
      dt(dt),

      r_a(contact.a - A->get_polygon().get_centroid()),
      r_b(contact.b - B->get_polygon().get_centroid()),
      n(contact.normal),
      t(contact.tangent),

      j_va(-1*n),
      j_wa(-1*r_a.cross(n)),
      j_vb(n),
      j_wb(r_b.cross(n)),

      j_va_t(-1*t),
      j_wa_t(-1*r_a.cross(t)),
      j_vb_t(t),
      j_wb_t(r_b.cross(t)),

      a_inv_mass(A->get_invMass()),
      b_inv_mass(B->get_invMass()),
      a_inv_inertia(A->get_invInertia()),
      b_inv_inertia(B->get_invInertia()),

      m_eff( 1/(a_inv_mass + j_wa.dot(a_inv_inertia*j_wa) + b_inv_mass + j_wb.dot(b_inv_inertia*j_wb)) ),
      m_eff_t( 1/(a_inv_mass + j_wa_t.dot(a_inv_inertia*j_wa_t) + b_inv_mass + j_wb_t.dot(b_inv_inertia*j_wb_t)) ),

      c_r(A->get_restitution()*B->get_restitution()),
      c_f(A->get_friction()*B->get_friction()),

      m_total_lambda(0),
      m_total_lambda_t(0)
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
    float b = -(beta/dt)*d + c_r*closing_vel;

    float lambda = m_eff*(-(jv + b));
    float old_total_lambda = m_total_lambda;
    m_total_lambda = std::max(0.0f, m_total_lambda + lambda);
    lambda = m_total_lambda - old_total_lambda;

    A->add_vel(a_inv_mass*j_va*lambda);
    A->add_angVel((a_inv_inertia*j_wa*lambda).z);
    B->add_vel(b_inv_mass*j_vb*lambda);
    B->add_angVel((b_inv_inertia*j_wb*lambda).z);
    
    float jv_t =
        j_va_t.dot(a_vel)
      + j_wa_t.dot(a_angVel)
      + j_vb_t.dot(b_vel)
      + j_wb_t.dot(b_angVel);

    float lambda_t = m_eff*(-jv_t);
    float old_total_lambda_t = m_total_lambda_t;
    m_total_lambda_t = std::clamp(m_total_lambda_t + lambda_t, -c_f*m_total_lambda, c_f*m_total_lambda);
    lambda_t = m_total_lambda_t - old_total_lambda_t;

    A->add_vel(a_inv_mass*j_va_t*lambda_t);
    A->add_angVel((a_inv_inertia*j_wa_t*lambda_t).z);
    B->add_vel(b_inv_mass*j_vb_t*lambda_t);
    B->add_angVel((b_inv_inertia*j_wb_t*lambda_t).z);
}