#include "window.h"
#include <iostream>

namespace Engine
{
    Window::Window(int width, int height)
        : m_window(nullptr),
          m_renderer(nullptr),
          m_running(true),
          m_paused(false)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            SDL_Log("SDL_Error: %s", SDL_GetError());
        } else {
            m_window = SDL_CreateWindow("2D Physics simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

            if (!m_window) {
                SDL_Log("SDL_CreateWindow: %s", SDL_GetError());
            } else {
                m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
                
                if (!m_renderer) {
                    SDL_Log("SDL_CreateRenderer: %s", SDL_GetError());
                }
            }
        }
    }

    Window::~Window()
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
        m_renderer = nullptr;

        SDL_Quit();
    }

    void Window::handle_events()
    {
        SDL_Event e;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                stop();
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_SPACE: toggle_pause(); break;
                }
            }
        }
    }

    void Window::loop(Physics::World& world)
    {
        while (m_running) {
            handle_events();
            
            if (!m_paused) {
                SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(m_renderer);
                
                world.step(m_timer.get_dt());
                render_world(world);

                SDL_RenderPresent(m_renderer);
            }
        }
    }

    void Window::stop()
    {
        m_running = false;
    }

    void Window::toggle_pause()
    {
        m_paused = !m_paused;
        m_timer.toggle_pause();
    }

    void Window::render_polygon(const Physics::Math::Polygon& polygon)
    {
        std::vector<Physics::Math::Vector2> vertices = polygon.get_vertices();
        std::size_t n = vertices.size();
        std::size_t prev = n-1;
        Physics::Math::Vector2 a, b;

        SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);

        for (std::size_t i = 0; i < n; i++) {
            a = vertices[i];
            b = vertices[prev];
            SDL_RenderDrawLine(m_renderer, a.x, invert_y(a.y), b.x, invert_y(b.y));

            prev = i;
        }
    }

    void Window::render_world(const Physics::World& world)
    {
        for ( Physics::Dynamics::CollisionBody* object : world.get_objects() ) {
            render_polygon(object->get_polygon());
        }
    }

    float Window::invert_y(float y)
    {
        int height;
        SDL_GetWindowSize(m_window, nullptr, &height);

        return height - y;
    }
}