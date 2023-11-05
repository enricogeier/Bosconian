#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Vector2.h"
#include "Rectangle.h"


class Player
{
private:
    static const Vector2 START_POSITION;
    static const float MAX_VELOCITY;
    static const float MIN_VELOCITY;
    Vector2 clamped_direction;

    int player_lives = 3;

public:
    std::vector<Rectangle> player_sprites;

    Vector2 position;
    Vector2 direction = Vector2(0.0f, 0.0f);

    explicit Player(Vector2 direction = Vector2(0.0f, 0.0f));

    void move(Vector2& new_direction, float& delta);

};


#endif