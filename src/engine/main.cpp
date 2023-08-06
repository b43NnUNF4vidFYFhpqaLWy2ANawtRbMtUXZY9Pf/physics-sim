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
    Vector2 a_1(500, 500);
    Vector2 a_2(500, 600);
    Vector2 a_3(600, 600);
    Vector2 a_4(600, 500);
    
    Polygon a({a_1, a_2, a_3, a_4});
    RigidBody a_body(a, 500, 0.1);
    a_body.add_angVel(0.78);
    
    Vector2 b_1(500, 200);
    Vector2 b_2(500, 300);
    Vector2 b_3(600, 300);
    Vector2 b_4(600, 200);

    Polygon b({b_1, b_2, b_3, b_4});
    RigidBody b_body(b, 500, 0.1);
    b_body.add_angVel(-0.78);

    World world;
/*     Vector2 gravity(0.0, -9.82);
    world.set_gravity(gravity); */
    world.set_gravity_point({SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, 10*9.82);
    world.add_object(&a_body);
    world.add_object(&b_body);
    
    ContactConstraintSolver contact_solver(6, 0.1);
    world.add_solver(&contact_solver);

    Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
    window.loop(world);
    
    return EXIT_SUCCESS;
}