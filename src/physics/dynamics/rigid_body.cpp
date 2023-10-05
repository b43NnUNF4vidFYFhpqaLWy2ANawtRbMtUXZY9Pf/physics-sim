#include "rigid_body.h"
#include <vector>
#include <cstddef>
#include <cmath>

namespace Physics::Dynamics
{
    RigidBody::RigidBody(Physics::Math::Polygon polygon, float mass, float restitution, float friction)
        : CollisionBody(polygon),
          m_mass(mass),
          m_restitution(restitution),
          m_friction(friction),
          m_invMass(1/mass),
          m_angularVelocity(0),
          m_torque(0)
    {
        calc_moment_of_inertia();
    }

    Physics::Math::Vector2 RigidBody::get_vel() const
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

    void RigidBody::add_vel(const Physics::Math::Vector2& v)
    {
        m_vel += v;
    }
    void RigidBody::add_angVel(float a)
    {
        m_angularVelocity += a;
    }

    void RigidBody::apply_force(const Physics::Math::Vector2& f, const Physics::Math::Vector2& p)
    {
        m_force += f;
        
        Physics::Math::Vector2 r = p - m_polygon.get_centroid();
        m_torque += r.cross(f).z;
    }

    void RigidBody::update_vel(float dt)
    {
        m_vel += (m_force/m_mass)*dt;
        m_force = {0, 0, 0};
        
        m_angularVelocity += (m_torque/m_inertia)*dt;
        m_torque = 0.0f;
    }

    void RigidBody::update_pos(float dt)
    {
        m_polygon.move(m_vel*dt);
        m_polygon.rotate(m_angularVelocity*dt);
    }

    void RigidBody::calc_moment_of_inertia()
    {
        // https://stackoverflow.com/a/58983642
        float area = 0.0f;
        Physics::Math::Vector2 center(0.0f, 0.0f, 0.0f);

        std::vector<Physics::Math::Vector2> vertices = m_polygon.get_vertices();
        std::size_t n = vertices.size();
        std::size_t prev = n-1;

        Physics::Math::Vector2 centroid = m_polygon.get_centroid();
        Physics::Math::Vector2 a;
        Physics::Math::Vector2 b;
        float area_tri;
        Physics::Math::Vector2 center_tri;
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