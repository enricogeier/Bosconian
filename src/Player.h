#ifndef PLAYER_H
#define PLAYER_H

#include <utility>

#include "GameObject.h"

class Player : public GameObject
{
private:
    static const Vector2 START_POSITION;
    static const float MAX_VELOCITY;
    static const float MIN_VELOCITY;

    int player_lives = 3;

public:

    Vector2 clamped_direction;
    std::vector<Rectangle> explosion_sprites;

    Vector2 direction = Vector2(0.0f, -1.0f);

    explicit Player(std::vector<Rectangle> normal_sprites = {}, std::vector<Rectangle> explosion_sprites = {}, CollisionCircle collision_circle = CollisionCircle())
    : explosion_sprites(std::move(explosion_sprites)),  GameObject(START_POSITION, std::move(normal_sprites), std::move(collision_circle))
    {
    }

    void move(Vector2& new_direction, float& delta);

};


#endif