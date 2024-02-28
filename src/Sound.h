#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>


class Sound
{
private:

    Mix_Chunk* explosion = nullptr;
    Mix_Chunk* shoot = nullptr;
    Mix_Chunk* startFanfare = nullptr;
    Mix_Chunk* endFanfare = nullptr;


public:

    explicit Sound();

    void playStartFanfare();

    void playExplosion();

    void playEndFanfare();

    void playShoot();

    // TODO: call after render loop !!!
    void close();

};


#endif