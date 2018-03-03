#ifndef TIMER_H
#define TIMER_H

//c++ std lib
#include <chrono>

//3rd party libs
#include <SDL2/SDL.h>

class Timer
{
    typedef std::chrono::steady_clock Clock;

public:
	Timer() {};
	~Timer() {};
	
        void start();
        void set_start(Clock::time_point _t);
        std::chrono::nanoseconds get_dur();
	
private:
        Clock::time_point start_tm;
};

#endif
