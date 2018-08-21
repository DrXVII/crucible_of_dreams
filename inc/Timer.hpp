#ifndef TIMER_H
#define TIMER_H

//c++ std lib
#include <chrono>

//3rd party libs
#include <SDL2/SDL.h>

/* TODO LOWEST_PRI
 * Compare the performance of this timer against c-style, possibly
 * platform-dependent, timers (e.g. using time.h).
 * Since this timer and operations associated with it perform well enough,
 * this is mainly a sporting excercise, not of any priority. */

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
