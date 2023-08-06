#include "window.h"
#include "vector.h"
#include "polygon.h"
#include "collision_body.h"
#include "rigid_body.h"
#include "world.h"
#include "contact_solver.h"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

int main()
{
    Vector2 a(500, 399);
    Vector2 b(500, 499);
    Vector2 c(600, 499);
    Vector2 d(600, 399);
    
    Polygon poly({a, b, c, d});
    RigidBody body(poly, 50, 0.25);
    
    Polygon ground_rect({ {300,300}, {300, 400}, {800, 400}, {800, 300} });
    RigidBody ground(ground_rect, 500, 0.25);

    World world;
    Vector2 gravity(0.0, -9.82);
    world.set_gravity(gravity);
    world.add_object(&body);
    world.add_object(&ground);
    
    ContactConstraintSolver contact_solver(10, 0.0005);
    world.add_solver(&contact_solver);

    Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
    window.loop(world);
    
    return EXIT_SUCCESS;
}