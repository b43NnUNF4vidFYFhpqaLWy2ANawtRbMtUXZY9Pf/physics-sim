#pragma once

#include <cstdint>

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
    double get_dt();
};