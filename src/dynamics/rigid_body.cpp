#include "rigid_body.h"
#include <cmath>
#include <cstddef>
#include <vector>

namespace Physics
{
    RigidBody::RigidBody(std::vector<Vector2> vertices, float mass, float restitution, float friction)
        : CollisionBody(vertices),
          m_angularVelocity(0),
          m_torque(0),
          m_mass(mass),
          m_invMass(1/mass),
          m_restitution(restitution),
          m_friction(friction)
    {
        calc_moment_of_inertia();
    }

    Vector2 RigidBody::get_vel() const
    {
        return m_vel;
    }

    float RigidBody::get_angVel() const
    {
        return m_angularVelocity;
    }

    float RigidBody::get_mass() const
    {
        return m_mass;
    }

    float RigidBody::get_invMass() const
    {
        return m_invMass;
    }

    float RigidBody::get_invInertia() const
    {
        return m_invInertia;
    }

    float RigidBody::get_restitution() const
    {
        return m_restitution;
    }

    float RigidBody::get_friction() const
    {
        return m_friction;
    }

    void RigidBody::add_vel(const Vector2& v)
    {
        m_vel += v;
    }
    void RigidBody::add_angVel(float a)
    {
        m_angularVelocity += a;
    }

    void RigidBody::apply_force(const Vector2& f, const Vector2& p)
    {
        m_force += f;
        
        Vector2 r = p - get_centroid();
        m_torque += r.cross(f).z;
    }

    void RigidBody::update_vel(float dt)
    {
        m_vel += m_invMass*(m_force*dt);
        m_force = {0, 0, 0};
        
        m_angularVelocity += m_invInertia*(m_torque*dt);
        m_torque = 0.0f;
    }

    void RigidBody::update_pos(float dt)
    {
        move(m_vel*dt);
        rotate(m_angularVelocity*dt);
    }

    void RigidBody::calc_moment_of_inertia()
    {
        // https://stackoverflow.com/a/58983642
        float area = 0.0f;
        Vector2 center(0.0f, 0.0f, 0.0f);

        std::vector<Vector2> vertices = get_vertices();
        std::size_t n = vertices.size();
        std::size_t prev = n-1;

        Vector2 centroid = get_centroid();
        Vector2 a;
        Vector2 b;
        float area_tri;
        Vector2 center_tri;
        float inertia_tri;

        for (std::size_t i = 0; i < n; i++) {
            a = vertices[prev] - centroid;
            b = vertices[i] - centroid;

            area_tri = std::abs(a.cross(b).z)/2;
            center_tri = (a+b)/3;
            inertia_tri = area_tri*(a.dot(a) + b.dot(b) + a.dot(b))/6;

            center = (center*area + center_tri*area_tri)/(area + area_tri);
            area += area_tri;
            m_inertia += inertia_tri;

            prev = i;
        }

        float density = m_mass/area;
        m_inertia *= density;
        m_inertia -= m_mass*center.dot(center);
        m_invInertia = 1/m_inertia;
    }
}
