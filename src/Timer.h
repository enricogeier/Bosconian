#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>
#include <iostream>

class Timer
{
private:
    Uint32 start_time = 0;
    Uint32 pause_time = 0;
    Uint32 time_left = 0;
    bool is_paused = false;
    bool is_started = false;
    bool is_stopped = false;


public:
    Timer()= default;

    void start();

    void stop();

    void pause();

    void resume();

    Uint32 get_current_time() const;


};


#endif
