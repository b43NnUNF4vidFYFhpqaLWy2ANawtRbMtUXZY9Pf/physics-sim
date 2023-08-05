#pragma once

#include "collision_body.h"
#include "vector.h"
#include "polygon.h"

class RigidBody : public CollisionBody
{
private:
    Vector2 m_vel;
    Vector2 m_force;
    float m_angularVelocity;
    float m_torque;
    
    float m_mass;
    float m_invMass;
    float m_inertia;
    float m_invInertia;

    void calc_moment_of_inertia();
public:
    RigidBody(Polygon polygon, float mass);

    Vector2 get_vel() const;
    float get_angVel() const;
    float get_mass() const;
    float get_invMass() const;
    float get_invInertia() const;
    
    void add_vel(const Vector2& v);
    void add_angVel(float a);

    void apply_force(const Vector2& f, const Vector2& p);
    void update_vel(double dt);
    void update_pos(double dt);
};