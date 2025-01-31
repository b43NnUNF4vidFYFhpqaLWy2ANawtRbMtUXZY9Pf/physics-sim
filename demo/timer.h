#pragma once

#include <cstdint>

namespace Engine
{
    class Timer
    {
    private:
        uint64_t m_old_time, m_new_time;
        bool m_started;
        bool m_paused;
    public:
        Timer();

        void start();
        void toggle_pause();
        float get_dt();
    };
}