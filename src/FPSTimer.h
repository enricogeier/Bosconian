#ifndef FPSTIMER_H
#define FPSTIMER_H

#include "Timer.h"


class FPSTimer : public Timer
{
private:
    const int MAX_FPS = 60;
    Uint64 previous_time = 0;
    const Uint64 time_for_frame =  1000 / MAX_FPS;
    Uint64 delta = 0;
public:

    FPSTimer()= default;

    float get_delta() const;

    void clamp_and_print_fps(const long int& amount_of_frames);

};


#endif
