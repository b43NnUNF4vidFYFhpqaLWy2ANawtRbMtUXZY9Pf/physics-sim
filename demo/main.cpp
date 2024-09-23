#include "window.h"
#include "vector.h"
#include "collision_body.h"
#include "bruteforce.h"
#include "bvh.h"
#include "world.h"
#include "contact_solver.h"
#include "plane_solver.h"

#include <vector>

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

int main()
{
    Physics::World world;
    Engine::Window window(SCREEN_WIDTH, SCREEN_HEIGHT, world);

    // Physics::Bruteforce collision_detector;
    // world.set_collision_detector(&collision_detector);

    Physics::AABBTree collision_detector(0.2);
    world.set_collision_detector(&collision_detector);

    Physics::Vector2 gravity(0.0, -10*9.82);
    world.set_gravity(gravity);

    Physics::PlaneConstraintSolver plane_solver(6, 0.8);
    world.add_solver(&plane_solver);
    Physics::ContactConstraintSolver contact_solver(6, 0.005, 0.05, 0.002);
    world.add_solver(&contact_solver);

    std::vector<Physics::Vector2> left = {
        {50, 360},
        {50, 385},
        {640, 385},
        {640, 360}
    };
    Physics::CollisionBody left_body(left);
    left_body.rotate(-0.785);
    world.add_object(&left_body);
    
    std::vector<Physics::Vector2> right = {
        {640, 360},
        {640, 385},
        {1230, 385},
        {1230, 360}
    };
    Physics::CollisionBody right_body(right);
    right_body.rotate(0.785);
    world.add_object(&right_body);

    std::vector<Physics::Vector2> ground_poly = { {50, 25}, {50, 50}, {1230, 50}, {1230, 25} };
    Physics::CollisionBody ground(ground_poly);
    world.add_object(&ground);
    
    window.loop();
    
    return EXIT_SUCCESS;
}
