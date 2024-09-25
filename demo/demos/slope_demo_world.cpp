#include "slope_demo_world.h"

namespace Engine
{
    SlopeDemoWorld::SlopeDemoWorld()
        : m_collision_detector(0.2),
          m_plane_solver(6, 0.8),
          m_contact_solver(6, 0.005, 0.05, 0.002),
          m_gravity(0.0, -10*9.82),
          m_left({{50, 360}, {50, 385}, {640, 385}, {640, 360}}),
          m_left_body(m_left),
          m_right({{640, 360}, {640, 385}, {1230, 385}, {1230, 360}}),
          m_right_body(m_right),
          m_ground_poly({{50, 25}, {50, 50}, {1230, 50}, {1230, 25}}),
          m_ground(m_ground_poly)
    {
        m_world.set_collision_detector(&m_collision_detector);
        m_world.add_solver(&m_plane_solver);
        m_world.add_solver(&m_contact_solver);
        m_world.set_gravity(m_gravity);
        m_world.add_object(&m_left_body);
        m_world.add_object(&m_right_body);
        m_world.add_object(&m_ground);

        m_ground.attach(&m_logger);

        m_left_body.rotate(-0.785);
        m_right_body.rotate(0.785);
    }

    SlopeDemoWorld::~SlopeDemoWorld()
    {
        m_ground.detach(&m_logger);
    }

    Physics::World& SlopeDemoWorld::get_world()
    {
        return m_world;
    }
}