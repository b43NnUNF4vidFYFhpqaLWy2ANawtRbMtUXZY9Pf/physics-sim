#include "window.h"

Window::Window(int width, int height)
    : m_window(nullptr),
      m_surface(nullptr),
      m_renderer(nullptr)
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

    m_running = true;
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
        }
    }
}

void Window::loop()
{
    while (m_running) {
        handle_events();
        
        SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_renderer);
        SDL_RenderPresent(m_renderer);
    }
}

void Window::stop()
{
    m_running = false;
}