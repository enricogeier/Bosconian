#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>


class Sound
{
private:

    Mix_Music* background = nullptr;

    Mix_Chunk* explosion = nullptr;
    Mix_Chunk* shot = nullptr;
    Mix_Chunk* startFanfare = nullptr;
    Mix_Chunk* endFanfare = nullptr;
    Mix_Chunk* gameOver = nullptr;


public:

    explicit Sound();

    void playStartFanfare();

    void playExplosion();

    void playEndFanfare();

    void playShot();

    void playGameOver();

    void stopBackground();

    // TODO: call after render loop !!!
    void close();

};


#endif