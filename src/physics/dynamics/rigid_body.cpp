#include "rigid_body.h"
#include <vector>
#include <cstddef>
#include <cmath>

RigidBody::RigidBody(Polygon polygon, float mass)
    : m_polygon(polygon),
      m_mass(mass),
      m_invMass(1/mass)
{
    calc_moment_of_inertia();
}

void RigidBody::apply_force(Vector3& f, Vector3& p)
{
    m_force += f;
    
    Vector3 r = p - m_polygon.get_centroid();
    m_torque = r.cross(f).z;
}

void RigidBody::step(float dt)
{
    m_vel = (m_force/m_mass)*dt;
    Vector3 delta_pos = m_vel*dt;
    m_polygon.move(delta_pos);
    m_force = {0, 0, 0};
    
    m_angularVelocity = (m_torque/m_inertia)*dt;
    m_angle = m_angularVelocity*dt;
    m_polygon.rotate(m_angle);
    m_torque = 0.0f;
}

void RigidBody::calc_moment_of_inertia()
{
    // https://stackoverflow.com/a/58983642
    float area = 0.0f;
    Vector3 center(0.0f, 0.0f, 0.0f);

    std::vector<Vector3> vertices = m_polygon.get_vertices();
    std::size_t n = vertices.size();
    std::size_t prev = n-1;

    Vector3 centroid = m_polygon.get_centroid();
    Vector3 a;
    Vector3 b;
    float area_tri;
    Vector3 center_tri;
    float inertia_tri;

    Vector3 temp_fix; // error: cannot bind non-const lvalue reference of type ‘Vector3&’ to an rvalue of type ‘Vector3’
    for (std::size_t i = 0; i < n; i++) {
        a = vertices[prev] - centroid;
        b = vertices[i] - centroid;

        area_tri = std::abs(a.cross(b).z)/2;
        center_tri = (a+b)/3;
        inertia_tri = area_tri*(a.dot(a) + b.dot(b) + a.dot(b))/6;

        temp_fix = center_tri*area_tri;
        center = (center*area + temp_fix)/(area + area_tri);
        area += area_tri;
        m_inertia += inertia_tri;

        prev = i;
    }

    float density = m_mass/area;
    m_inertia *= density;
    m_inertia -= m_mass*center.dot(center);
    m_invInertia = 1/m_inertia;
}