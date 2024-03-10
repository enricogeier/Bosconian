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

    /**
     * Constructs a new Sound object. Plays the background music infinitively.
     */
    explicit Sound();

    /**
     * plays the start fanfare track.
     */
    void playStartFanfare();

    /**
     * plays the explosion track.
     */
    void playExplosion();

    /**
     * plays the end fanfare track.
     */
    void playEndFanfare();

    /**
     * is called every time the player shoots. Plays shoot track.
     */
    void playShot();

    /**
     * is called when player has lost all lives. Plays game over track.
     */
    void playGameOver();

    /**
     * stops the background music.
     */
    void stopBackground();

    /**
     * Clears the Sound.
     */
    void close();

};


#endif