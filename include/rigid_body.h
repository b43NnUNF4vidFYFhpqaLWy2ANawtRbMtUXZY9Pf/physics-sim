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

    float get_mass() const;

    void apply_force(const Vector2& f, const Vector2& p);
    void step(double dt);
};