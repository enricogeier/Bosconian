#ifndef CELESTIALOBJECT_H
#define CELESTIALOBJECT_H

#include <utility>
#include <chrono>
#include "GameObject.h"


class Mine : public GameObject
{
private:
    std::chrono::microseconds explosion_start = std::chrono::microseconds (0);

public:
    std::chrono::microseconds explosion_duration = std::chrono::microseconds (300000); // 0.3s

    explicit Mine(Vector2 position, CollisionCircle collision_circle, Vector2 scale = Vector2(1.0f, 1.0f))
    : GameObject(position, std::move(collision_circle), Type::MINE, scale)
    {
    }

    void explode();

    bool check_explosion();


};


#endif CELESTIALOBJECT_H
