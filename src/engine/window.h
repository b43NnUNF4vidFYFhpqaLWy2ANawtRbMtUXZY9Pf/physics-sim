#pragma once

#include "collision.h"
#include "polygon.h"
#include "timer.h"
#include "world.h"
#include <SDL2/SDL.h>


namespace Engine
{
    class Window
    {
    private:
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        Timer m_timer;
        bool m_running;
        bool m_paused;

        Physics::World& m_world;
        
        void render_world();
        void render_polygon(const Physics::Polygon* const polygon);
        void render_collision(Physics::CollisionPair collision, float dt);
        float invert_y(float y);
    public:
        Window(int width, int height, Physics::World& world);
        ~Window();
        
        void handle_events();
        void loop();
        void stop();
        void toggle_pause();

        void set_render_collisions(Physics::CollisionBody* body);
    };
}
