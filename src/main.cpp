#include "window.h"
#include "vector.h"
#include "polygon.h"
#include "rigid_body.h"
#include "world.h"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

int main()
{
    Vector3 f(0.0f, 10.0f, 0.0f);

    Vector3 a(2.0f, 2.0f, 0.0f);
    Vector3 b(2.0f, 4.0f, 0.0f);
    Vector3 c(4.0f, 4.0f, 0.0f);
    Vector3 d(4.0f, 2.0f, 0.0f);
    
    Polygon poly({a, b, c, d});
    RigidBody body(poly, 10);

    World world;
    world.add_object(&body);
    
    Vector3 p(3.0f, 2.0f, 0.0f);
    body.apply_force(f, p);

    world.step(1);
    
/*     Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
    window.loop(); */
    
    return EXIT_SUCCESS;
}