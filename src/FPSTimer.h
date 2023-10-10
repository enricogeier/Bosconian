#ifndef FPSTIMER_H
#define FPSTIMER_H

#include "Timer.h"
#include "Settings.h"


class FPSTimer : public Timer
{
private:
    Uint32 previous_time = 0;
    const int time_for_frame = 1000 / MAX_FPS;
public:
    FPSTimer()= default;

    void print_fps(const int& amount_of_frames);

    void clamp_fps();


};


#endif
