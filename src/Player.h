#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "Vector2.h"
#include "Settings.h"


class Player
{
private:
    Vector2 clamped_direction;
    inline static const Vector2 START_POSITION = Vector2((float)SCREEN_SIZE_WIDTH / 2, (float)SCREEN_SIZE_HEIGHT / 2);
    inline static const float MAX_VELOCITY = 300.0f;
    inline static const float MIN_VELOCITY = 100.0f;

public:

    int lives{};

    Vector2 position;
    Vector2 direction = Vector2(0.0f, 0.0f);

    explicit Player(Vector2 direction = Vector2(0.0f, 0.0f),
           int lives = 3);

    void move(Vector2& new_direction, float& delta);

};


#endif