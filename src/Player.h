#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include "Vector2.h"
#include "Rectangle.h"


class Player
{
private:
    Vector2 clamped_direction;
    static const Vector2 START_POSITION;
    static const float MAX_VELOCITY;
    static const float MIN_VELOCITY;

    int player_lives = 3;

public:

    std::list<Rectangle> player_sprites;

    Vector2 position;
    Vector2 direction = Vector2(0.0f, 0.0f);

    explicit Player(Vector2 direction = Vector2(0.0f, 0.0f));

    void move(Vector2& new_direction, float& delta);

};


#endif