#include "Timer.h"

void Timer::start()
{
    if(is_stopped)
    {
        // reset timer
        this->is_paused = false;
        this->is_stopped = false;
        this->time_left = 0;
        this->pause_time = 0;
    }

    this->start_time = SDL_GetTicks();
    this->is_started = true;
}

void Timer::stop()
{
    if(!is_paused)
    {
        this->time_left = get_current_time();
    }


    is_stopped = true;
    is_started = false;
}

void Timer::pause()
{
    if(is_started && !is_paused)
    {
        this->time_left = get_current_time();
        is_paused = true;
    }

}

void Timer::resume()
{
    if(is_started && is_paused)
    {
        this->pause_time += SDL_GetTicks() - this->time_left;
        is_paused = false;

    }
}

Uint32 Timer::get_current_time() const
{
  if(!is_stopped && !is_paused)
  {
      return SDL_GetTicks() - this->pause_time - this->start_time;
  }
  else
  {
      return time_left;
  }

}