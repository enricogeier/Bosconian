#include "Sound.h"

Sound::Sound()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    explosion = Mix_LoadWAV("../Sounds/explosion.wav");
    shoot = Mix_LoadWAV("../Sounds/shoot.wav");
    startFanfare = Mix_LoadWAV("../Sounds/start_fanfare.wav");
    endFanfare = Mix_LoadWAV("../Sounds/end_fanfare.wav");

}


void Sound::playEndFanfare()
{
    Mix_PlayChannel(-1, endFanfare, 0);
}

void Sound::playExplosion()
{
    Mix_PlayChannel(-1, explosion, 0);
}

void Sound::playShoot()
{
    Mix_PlayChannel(-1, shoot, 0);
}

void Sound::playStartFanfare()
{
    Mix_PlayChannel(-1, startFanfare, 0);
}


void Sound::close()
{
    Mix_FreeChunk(shoot);
    Mix_FreeChunk(explosion);
    Mix_FreeChunk(startFanfare);
    Mix_FreeChunk(endFanfare);

    Mix_Quit();

}