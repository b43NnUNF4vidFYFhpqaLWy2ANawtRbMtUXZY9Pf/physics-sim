#include "window.h"
#include "vector.h"
#include <iostream>

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

int main()
{
    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b(2.0f, 3.0f, 4.0f);
    Vector3 c = a + b;
    
/*     Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
    window.loop(); */
    
    return EXIT_SUCCESS;
}