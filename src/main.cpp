#include "window.h"
#include "vector.h"
#include "polygon.h"
#include "rigid_body.h"
#include "world.h"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

int main()
{
    Vector2 a(500, 500);
    Vector2 b(500, 600);
    Vector2 c(600, 600);
    Vector2 d(600, 500);
    
    Polygon poly({a, b, c, d});
    RigidBody body(poly, 10);

    World world;
    Vector2 gravity(0.0, -9.82);
    world.set_gravity(gravity);
    world.add_object(&body);

    Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
    window.loop(world);
    
    return EXIT_SUCCESS;
}