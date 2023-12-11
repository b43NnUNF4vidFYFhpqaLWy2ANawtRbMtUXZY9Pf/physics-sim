#include "window.h"
#include "vector.h"
#include "polygon.h"
#include "collision_body.h"
#include "rigid_body.h"
#include "bvh.h"
#include "world.h"
#include "contact_solver.h"
#include "plane_solver.h"

#include <vector>
#include <memory>
#include <utility>

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

int main()
{
    Physics::World world;
    Physics::AABBTree collision_detector(0.2);
    world.set_collision_detector(&collision_detector);

    Physics::Vector2 gravity(0.0, -10*9.82);
    world.set_gravity(gravity);

    Physics::PlaneConstraintSolver plane_solver(6, 0.8);
    world.add_solver(&plane_solver);
    Physics::ContactConstraintSolver contact_solver(6, 0.2);
    world.add_solver(&contact_solver);

    const int square_size = 10;
    const int columns = 50;
    const int rows = 5;
    const int column_interval = SCREEN_WIDTH/columns;
    const int row_interval = column_interval;
    const int row_height = rows*row_interval;
    
    const float square_mass = 100;
    const float square_restitution = 0.2;
    const float square_friction = 0.1;

    std::vector<std::unique_ptr<Physics::RigidBody>> squares; // Physics engine itself does not take care of memory management
    squares.reserve(columns*rows);
    world.reserve_objects(columns*rows);

    for (int i = 0; i < SCREEN_WIDTH; i += column_interval) {
        for (int j = 0; j < row_height; j += row_interval) {
            Physics::Polygon poly({
                    {
                        i,
                        SCREEN_HEIGHT - j - square_size
                    },
                    {
                        i,
                        SCREEN_HEIGHT - j
                    },
                    {
                        i + square_size,
                        SCREEN_HEIGHT - j
                    },
                    {
                        i + square_size,
                        SCREEN_HEIGHT - j - square_size
                    }
                });
            std::unique_ptr<Physics::RigidBody> body = std::make_unique<Physics::RigidBody>(Physics::RigidBody(poly, square_mass, square_restitution, square_friction));
            world.add_object(body.get());
            
            squares.push_back(std::move(body));
        }
    }
    
    Physics::Polygon left({
        {50, 360},
        {50, 385},
        {640, 385},
        {640, 360}
    });
    left.rotate(-0.785);
    Physics::CollisionBody left_body(left);
    world.add_object(&left_body);
    
    Physics::Polygon right({
        {640, 360},
        {640, 385},
        {1230, 385},
        {1230, 360}
    });
    right.rotate(0.785);
    Physics::CollisionBody right_body(right);
    world.add_object(&right_body);

    Physics::Polygon ground_poly( { {50, 25}, {50, 50}, {1230, 50}, {1230, 25} } );
    Physics::CollisionBody ground(ground_poly);
    world.add_object(&ground);
    
    Engine::Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
    window.loop(world);
    
    return EXIT_SUCCESS;
}
