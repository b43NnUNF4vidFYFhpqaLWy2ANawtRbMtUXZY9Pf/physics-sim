#include "timer.h"
#include <SDL2/SDL.h>

namespace Engine
{
    Timer::Timer()
        : m_started(false),
          m_paused(false)
    {
    }

    void Timer::start()
    {
        m_started = true;
        m_old_time = SDL_GetTicks64();
    }

    void Timer::toggle_pause()
    {
        if (m_started && m_paused) {
            m_old_time = SDL_GetTicks64();
        }

        m_paused = !m_paused;
    }

    float Timer::get_dt()
    {
        float dt;
        
        if (m_paused) return 0;
        if (!m_started) start();
        
        m_new_time = SDL_GetTicks64();
        dt = (float)(m_new_time - m_old_time)/1000;
        m_old_time = m_new_time;
        
        return dt;
    }
}