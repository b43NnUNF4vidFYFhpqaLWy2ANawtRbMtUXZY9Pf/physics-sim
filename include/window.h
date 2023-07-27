#pragma once

#include <SDL2/SDL.h>

class Window
{
private:
    SDL_Window* m_window;
    SDL_Surface* m_surface;
    SDL_Renderer* m_renderer;
    bool m_running;
public:
    Window(int width, int height);
    ~Window();
    
    void handle_events();
    
    void loop();
    void stop();
};