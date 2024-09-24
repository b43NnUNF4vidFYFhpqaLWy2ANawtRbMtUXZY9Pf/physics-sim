#include "window.h"
#include "demos/slope_demo_world.h"

#include <vector>

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

int main()
{
    Engine::SlopeDemoWorld demo_world = Engine::SlopeDemoWorld();
    Physics::World world = demo_world.get_world();

    Engine::Window window(SCREEN_WIDTH, SCREEN_HEIGHT, world);
    window.loop();
    
    return EXIT_SUCCESS;
}
