#include "window.h"
#include "vector.h"
#include "polygon.h"
#include "collision_body.h"
#include "rigid_body.h"
#include "world.h"
#include "contact_solver.h"
#include "plane_solver.h"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

int main()
{
    Polygon a({ {500, 400}, {500, 500}, {600, 500}, {600, 400} });
    RigidBody a_body(a, 500, 0.1, 0.5);
    a_body.add_angVel(3.14);
    
    Polygon b({ {575, 200}, {575, 300}, {675, 300}, {675, 200} });
    RigidBody b_body(b, 500, 0.1, 0.5);
    
    Polygon ground_poly( { {100, 100}, {100, 200}, {550, 200}, {950, 150}, {1200, 100} } );
    CollisionBody ground(ground_poly);

    World world(0.2);
    Vector2 gravity(0.0, -10*9.82);
    world.set_gravity(gravity);
    world.add_object(&a_body);
    world.add_object(&b_body);
    world.add_object(&ground);
    
    PlaneConstraintSolver plane_solver(6, 0.8);
    world.add_solver(&plane_solver);
    ContactConstraintSolver contact_solver(6, 0.2);
    world.add_solver(&contact_solver);

    Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
    window.loop(world);
    
    return EXIT_SUCCESS;
}