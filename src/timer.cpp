#include "timer.h"
#include <SDL2/SDL.h>

Timer::Timer()
    : m_started(false)
{
}

void Timer::start()
{
    m_started = true;
    m_old_time = SDL_GetTicks64();
}

float Timer::get_dt()
{
    float dt;
    
    if (!m_started) start();
    
    m_new_time = SDL_GetTicks64();
    dt = (float)(m_new_time - m_old_time)/1000;
    m_old_time = m_new_time;
    
    return dt;
}