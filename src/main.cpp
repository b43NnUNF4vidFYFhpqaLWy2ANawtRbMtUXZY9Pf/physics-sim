#include "window.h"
#include "vector.h"
#include "polygon.h"
#include "rigid_body.h"
#include "world.h"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

int main()
{
    Vector3 a(500, 500, 0);
    Vector3 b(500, 600, 0);
    Vector3 c(600, 600, 0);
    Vector3 d(600, 500, 0);
    
    Polygon poly({a, b, c, d});
    RigidBody body(poly, 10);

    World world;
    Vector3 gravity(0.0f, -9.82f, 0.0f);
    world.set_gravity(gravity);
    world.add_object(&body);

    Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
    window.loop(world);
    
    return EXIT_SUCCESS;
}