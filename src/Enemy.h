#ifndef FLYINGENEMY_H
#define FLYINGENEMY_H

#include <utility>
#include "GameObject.h"

class Enemy : public GameObject
{
private:
    bool leader_of_formation = false;
public:

    std::vector<Rectangle> explosion_sprites;
    Vector2 start_position;


    explicit Enemy(Vector2 position, const std::vector<Rectangle>& player_sprite, const std::vector<Rectangle>& explosion_sprite, CollisionCircle collision_circle)
    : GameObject(position, player_sprite, std::move(collision_circle)), explosion_sprites(explosion_sprite),
      start_position(position)
    {
    }

    void move(Vector2& move_direction, float& delta);

};


#endif
