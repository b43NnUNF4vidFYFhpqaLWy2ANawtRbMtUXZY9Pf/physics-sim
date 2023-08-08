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
    Vector2 a_1(500, 400);
    Vector2 a_2(500, 500);
    Vector2 a_3(600, 500);
    Vector2 a_4(600, 400);
    
    Polygon a({a_1, a_2, a_3, a_4});
    RigidBody a_body(a, 500, 0.1);
    a_body.add_angVel(3.14);
    
    Vector2 b_1(575, 200);
    Vector2 b_2(575, 300);
    Vector2 b_3(675, 300);
    Vector2 b_4(675, 200);

    Polygon b({b_1, b_2, b_3, b_4});
    RigidBody b_body(b, 500, 0.1);
    
    Polygon ground_poly( { {100, 100}, {100, 200}, {550, 200}, {950, 150}, {1200, 100} } );
    CollisionBody ground(ground_poly);

    World world;
    Vector2 gravity(0.0, -10*9.82);
    world.set_gravity(gravity);
    world.add_object(&a_body);
    world.add_object(&b_body);
    world.add_object(&ground);
    
    PlaneConstraintSolver plane_solver(6, 0.2);
    world.add_solver(&plane_solver);
    ContactConstraintSolver contact_solver(6, 0.2);
    world.add_solver(&contact_solver);

    Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
    window.loop(world);
    
    return EXIT_SUCCESS;
}