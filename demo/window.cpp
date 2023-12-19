#include "window.h"
#include "SDL_render.h"
#include "rigid_body.h"
#include <SDL_mouse.h>

namespace Engine
{
    Window::Window(int width, int height, Physics::World& world)
        : m_window(nullptr),
          m_renderer(nullptr),
          m_running(true),
          m_paused(false),
          m_world(world)
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
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                gen_random();
            }
        }
    }

    void Window::loop()
    {
        while (m_running) {
            handle_events();
            
            if (!m_paused) {
                SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(m_renderer);
                
                m_world.step(m_timer.get_dt());
                render_world();

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

    void Window::set_render_collisions(Physics::CollisionBody* body)
    {
        // Can't pass a non-static member function as below, as
        // the 'this' parameter is an implicit parameter
        // body->set_collision_callback(render_collision);
        body->set_collision_callback([this](Physics::CollisionPair collision, float dt)
                                     {render_collision(collision, dt);}
                                     );
    }

    void Window::gen_random()
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        y = invert_y(y);
        
        Physics::Polygon polygon = Physics::Polygon::gen_random(50, {static_cast<float>(x), static_cast<float>(y)});
        std::unique_ptr<Physics::RigidBody> body = std::make_unique<Physics::RigidBody>(polygon.get_vertices(), 50, 0.2, 0.5);
        set_render_collisions(body.get());
        m_world.add_object(body.get());
        
        m_generated.push_back(std::move(body));
    }

    void Window::render_world()
    {
        for ( const Physics::CollisionBody* object : m_world.get_objects() ) {
            render_polygon(object);
        }
    }

    void Window::render_polygon(const Physics::Polygon* const polygon)
    {
        std::vector<Physics::Vector2> vertices = polygon->get_vertices();
        std::size_t n = vertices.size();
        std::size_t prev = n-1;
        Physics::Vector2 a, b;

        SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);

        for (std::size_t i = 0; i < n; i++) {
            a = vertices[i];
            b = vertices[prev];
            SDL_RenderDrawLine(m_renderer, a.x, invert_y(a.y), b.x, invert_y(b.y));

            prev = i;
        }
    }

    void Window::render_collision(Physics::CollisionPair collision, float dt)
    {
        SDL_SetRenderDrawColor(m_renderer, 0x00, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(m_renderer, collision.contact.a.x, invert_y(collision.contact.a.y), collision.contact.b.x, invert_y(collision.contact.b.y));
    }

    float Window::invert_y(float y)
    {
        int height;
        SDL_GetWindowSize(m_window, nullptr, &height);

        return height - y;
    }
}
