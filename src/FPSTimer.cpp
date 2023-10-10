#include "FPSTimer.h"

void FPSTimer::print_fps(const int &amount_of_frames)
{
    float fps = (amount_of_frames / (get_current_time() / 1000.0f));
    std::cout << std::to_string(fps) << std::endl;
}

void FPSTimer::clamp_fps()
{
    Uint32 current_time = get_current_time();
    Uint32 current_frame_time = current_time - previous_time;
    if(current_frame_time < time_for_frame + 1)
    {
        Uint32 delay_time = time_for_frame - current_frame_time;
        SDL_Delay(delay_time);
    }

    previous_time = current_time;


}