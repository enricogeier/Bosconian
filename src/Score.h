#ifndef SCORE_H
#define SCORE_H

#include "GameObject.h"
#include "Sound.h"


class Score
{
private:
    short P_ASTEROIDS = 10;
    short P_MINE = 20;
    short P_ITYPE = 50;
    short P_PTYPE = 60;
    short P_ETYPE = 70;
    short CANNON = 200;
     short SPACE_STATION = 1500;

    Sound* sound = nullptr;

public:

    int score = 0;
    int highscore = 20000;

    short space_stations = 0;

    /**
     * Constructs a new Sound object.
     *
     * @param sound Sound reference to play explosion sounds if an object was destroyed.
     */
    explicit Score(Sound* sound = nullptr);

    /**
     * Called if a collision happened.
     *
     * @param type Type of object which has been destroyed. See enum Type.
     */
    void increase_score(Type type);


};


#endif
