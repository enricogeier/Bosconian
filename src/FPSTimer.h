#ifndef FPSTIMER_H
#define FPSTIMER_H

#include "Timer.h"
#include "Settings.h"


class FPSTimer : public Timer
{
private:
    Uint32 previous_time = 0;
    const Uint32 time_for_frame =  1000 / MAX_FPS;
    Uint32 delta = 0;
public:

    FPSTimer()= default;

    float get_delta() const;

    void clamp_and_print_fps(const int& amount_of_frames);

};


#endif
