#ifndef SCORE_H
#define SCORE_H

#include "GameObject.h"

class Score
{
private:
    const short P_ASTEROIDS = 10;
    const short P_MINE = 20;
    const short P_ITYPE = 50;
    const short P_PTYPE = 60;
    const short P_ETYPE = 70;
    const short CANNON = 200;
    const short SPACE_STATION = 1500;

public:

    int score = 0;
    int highscore = 20000;

    short space_stations = 0;

    Score() = default;

    void increase_score(Type type);


};


#endif
