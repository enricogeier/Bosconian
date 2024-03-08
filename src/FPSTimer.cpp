#include "FPSTimer.h"


float FPSTimer::get_delta() const
{
    return (float)delta / 1000;
}

void FPSTimer::clamp_fps(const long int &amount_of_frames)
{
    Uint64 current_time = get_current_time();


    delta = current_time - previous_time;
    Uint32 delay_time = 0;
    if(delta < time_for_frame)
    {
        delay_time = time_for_frame - delta;
        SDL_Delay(delay_time);

    }

    previous_time = get_current_time();
    delta += previous_time - current_time;

    // calculate fps
    //float fps = ( amount_of_frames / (get_current_time() / 1000.0f));
    //std::cerr << std::to_string(fps) << std::endl;



}