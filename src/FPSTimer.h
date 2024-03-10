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

    /**
     * Constructs a new FPSTimer object.
     */
    FPSTimer()= default;

    /**
     * Retrieves the time between two frames in seconds.
     * @return Time between two frames in seconds.
     */
    float get_delta() const;

    /**
     * Clamps fps to a given value. The program creates around MAX_FPS frames in one second.
     * @param amount_of_frames Amount of frames calculated since program start.
     */
    void clamp_fps(const long int& amount_of_frames);

};


#endif
