#include "Score.h"

Score::Score(Sound* sound)
{
    this->sound = sound;
}

void Score::increase_score(Type type)
{
    switch(type)
    {

        case Type::E_TYPE:
        {
            score += 70;
            break;
        }

        case Type::P_TYPE:
        {
            score += 60;
            break;
        }

        case Type::I_TYPE:
        {
            score += 50;
            break;
        }

        case Type::ASTEROID:
        {
            score += 10;
            break;
        }

        case Type::MINE:
        {
            score += 20;
            break;
        }

        case Type::SPACE_STATION:
        {
            space_stations--;
            score += 1500;

            break;
        }

        case Type::CANNON:
        {
            score += 200;
            break;
        }


    }

    if(score > highscore)
    {
        if(score <= 99999999)
        {
            highscore = score;
        }
        else
        {
            highscore = 99999999;
            score = 99999999;
        }

    }

    sound->playExplosion();
}

