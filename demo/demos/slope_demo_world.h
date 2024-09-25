#pragma once

#include "demo_world.h"
#include "bvh.h"
#include "collision_logger.h"
#include "plane_solver.h"
#include "contact_solver.h"

#include <vector>

namespace Engine
{
    class SlopeDemoWorld : public DemoWorld
    {
    protected:
        Physics::World m_world;
        Physics::AABBTree m_collision_detector;
        Engine::CollisionLogger m_logger;
        Physics::PlaneConstraintSolver m_plane_solver;
        Physics::ContactConstraintSolver m_contact_solver;
        Physics::Vector2 m_gravity;
        std::vector<Physics::Vector2> m_left;
        Physics::CollisionBody m_left_body;
        std::vector<Physics::Vector2> m_right;
        Physics::CollisionBody m_right_body;
        std::vector<Physics::Vector2> m_ground_poly;
        Physics::CollisionBody m_ground;
    public:
        SlopeDemoWorld();
        ~SlopeDemoWorld();

        Physics::World& get_world() override;
    };
}