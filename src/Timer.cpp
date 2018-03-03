#include "Timer.hpp"

void Timer::start() { this->start_tm = Clock::now(); }
void Timer::set_start(Clock::time_point _t) { this->start_tm = _t; }


std::chrono::nanoseconds Timer::get_dur()
{
    return Clock::now() - this->start_tm;
}
