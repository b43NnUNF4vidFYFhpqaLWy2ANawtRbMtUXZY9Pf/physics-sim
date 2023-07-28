#pragma once

#include "vector.h"
#include "polygon.h"

class RigidBody
{
private:
    Polygon m_polygon;
    Vector3 m_vel;
    Vector3 m_force;

    float m_angle;
    float m_angularVelocity;
    float m_torque;
    
    float m_mass;
    float m_invMass;
    float m_inertia;
    float m_invInertia;

    void calc_moment_of_inertia();
public:
    RigidBody(Polygon polygon, float mass);
    void apply_force(Vector3& f, Vector3& p);
    void step(float dt);
};