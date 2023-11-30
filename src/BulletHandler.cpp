#include "BulletHandler.h"


void BulletHandler::insert_player_bullets(Vector2 &player_position, Vector2& player_direction, Vector2 &player_clamped_direction, CollisionCircle collision_circle) {
    if (player_direction.x == 1.0f) {
        if (player_direction.y == 1.0f) {
            bullet_list.push_back(Bullet(
                    Vector2(player_position.x + 5, player_position.y),
                    player_clamped_direction * (-1),
                    collision_circle
            ));

            bullet_list.push_back(Bullet(
                    Vector2(player_position.x + 21,
                            player_position.y + 15),
                    player_clamped_direction,
                    collision_circle
            ));

            bullet_list.back().speed *= 2;

        } else if (player_direction.y == 0.0f) {

            bullet_list.push_back(Bullet(
                    Vector2(player_position.x - 15, player_position.y + 3),
                    player_clamped_direction * (-1),
                    collision_circle
            ));

            bullet_list.push_back(Bullet(
                    Vector2(player_position.x + 16,
                            player_position.y + 3),
                    player_clamped_direction,
                    collision_circle
            ));

            bullet_list.back().speed *= 2;
        } else if (player_direction.y == -1.0f) {
            bullet_list.push_back(Bullet(
                    Vector2(player_position.x + 4, player_position.y),
                    player_clamped_direction,
                    collision_circle
            ));

            bullet_list.back().speed *= 2;

            bullet_list.push_back(Bullet(
                    Vector2(player_position.x - 12,
                            player_position.y + 15),
                    player_clamped_direction * (-1),
                    collision_circle
            ));


        }
    } else if (player_direction.x == 0.0f) {

        if (player_direction.y == 1.0f) {
            bullet_list.push_back(Bullet(
                    Vector2(player_position.x + 8, player_position.y - 15),
                    player_clamped_direction * (-1),
                    collision_circle
            ));

            bullet_list.push_back(Bullet(
                    Vector2(player_position.x + 8, player_position.y + 16),
                    Vector2(0, 1),
                    collision_circle
            ));

            bullet_list.back().speed *= 2;


        } else if (player_direction.y == -1.0f) {
            bullet_list.push_back(Bullet(
                    Vector2(player_position.x + 3, player_position.y - 15),
                    player_clamped_direction,
                    collision_circle
            ));

            bullet_list.back().speed *= 2;

            bullet_list.push_back(Bullet(
                    Vector2(player_position.x + 3, player_position.y + 16),
                    player_clamped_direction * (-1),
                    collision_circle
            ));


        }
    } else if (player_direction.x == -1.0f) {
        if (player_direction.y == 1.0f) {
            bullet_list.push_back(Bullet(
                    Vector2(player_position.x + 11, player_position.y),
                    player_clamped_direction * (-1),
                    collision_circle
            ));

            bullet_list.push_back(Bullet(
                    Vector2(player_position.x - 5,
                            player_position.y + 15),
                    player_clamped_direction,
                    collision_circle
            ));

            bullet_list.back().speed *= 2;

        } else if (player_direction.y == 0.0f) {
            bullet_list.push_back(Bullet(
                    Vector2(player_position.x, player_position.y + 3),
                    player_clamped_direction,
                    collision_circle
            ));

            bullet_list.back().speed *= 2;


            bullet_list.push_back(Bullet(
                    Vector2(player_position.x + 16, player_position.y + 3),
                    player_clamped_direction * (-1),
                    collision_circle
            ));


        } else if (player_direction.y == -1.0f) {

            bullet_list.push_back(Bullet(
                    Vector2(player_position.x, player_position.y),
                    player_clamped_direction,
                    collision_circle
            ));

            bullet_list.back().speed *= 2;

            bullet_list.push_back(Bullet(
                    Vector2(player_position.x + 16,
                            player_position.y + 15),
                    player_clamped_direction * (-1),
                    collision_circle
            ));



        }
    }
}

std::list<Bullet> &BulletHandler::get_bullets()
{
    return this->bullet_list;
}

void BulletHandler::check_collisions(QuadTree &quad_tree)
{
    for(auto& bullet : bullet_list)
    {
        quad_tree.check_collision(bullet);
    }
}

void BulletHandler::move_player_bullet(Vector2& position, Vector2& clamped_direction, QuadTree& quad_tree, float &delta)
{
    for(auto bullet = bullet_list.begin(); bullet != bullet_list.end();)
    {
        float border = 1000.0f;

        if(Vector2::distance(position, bullet->position) > border || bullet->state == State::EXPLODE)
        {
            bullet = bullet_list.erase(bullet);
        }
        else
        {

            if(bullet->speed != 1200 && bullet->clamped_direction == clamped_direction)
            {
                bullet->speed *= 2;
            }
            else if(bullet->speed == 1200 && bullet->clamped_direction != clamped_direction)
            {
                bullet->speed /= 2;
            }

            bullet->move(delta);
            quad_tree.insert(*bullet);

            ++bullet;
        }

    }
}