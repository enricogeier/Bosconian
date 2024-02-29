#include "Sound.h"

Sound::Sound()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    explosion = Mix_LoadWAV("../Sounds/explosion.wav");
    shot = Mix_LoadWAV("../Sounds/shot.wav");
    startFanfare = Mix_LoadWAV("../Sounds/start_fanfare.wav");
    endFanfare = Mix_LoadWAV("../Sounds/end_fanfare.wav");
    gameOver = Mix_LoadWAV("../Sounds/game_over.wav");

    background = Mix_LoadMUS("../Sounds/background.ogg");
    Mix_PlayMusic(background, -1);

}


void Sound::playEndFanfare()
{
    Mix_PlayChannel(-1, endFanfare, 0);
}

void Sound::playExplosion()
{
    Mix_PlayChannel(-1, explosion, 0);
}

void Sound::playShot()
{
    Mix_PlayChannel(-1, shot, 0);
}

void Sound::playStartFanfare()
{
    Mix_PlayChannel(-1, startFanfare, 0);
}

void Sound::playGameOver()
{
    Mix_PlayChannel(-1, gameOver, 0);
}

void Sound::stopBackground()
{
    Mix_HaltMusic();
}

void Sound::close()
{
    Mix_FreeMusic(background);

    Mix_FreeChunk(shot);
    Mix_FreeChunk(explosion);
    Mix_FreeChunk(startFanfare);
    Mix_FreeChunk(endFanfare);
    Mix_FreeChunk(gameOver);

    Mix_Quit();

}