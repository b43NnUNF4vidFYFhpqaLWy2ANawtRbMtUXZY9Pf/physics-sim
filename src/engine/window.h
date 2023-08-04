#pragma once

#include "polygon.h"
#include "world.h"
#include "timer.h"
#include <SDL2/SDL.h>

class Window
{
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    Timer m_timer;
    bool m_running;
    bool m_paused;
    
    float invert_y(float y);
    void render_polygon(const Polygon& polygon);
    void render_world(const World& world);
public:
    Window(int width, int height);
    ~Window();
    
    void handle_events();
    void loop(World& world);
    void stop();
    void toggle_pause();
};