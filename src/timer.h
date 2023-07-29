#pragma once

#include <cstdint>

class Timer
{
private:
    uint64_t m_old_time, m_new_time;
    bool m_started;
public:
    Timer();

    void start();
    float get_dt();
};