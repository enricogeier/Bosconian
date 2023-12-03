#include "BulletHandler.h"


void BulletHandler::insert_player_bullets(Player& player,  CollisionManager& collision_manager) {
    if (player.direction.x == 1.0f) {
        if (player.direction.y == 1.0f) {
            bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 5, player.position.y),
                    player.clamped_direction * (-1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 21,
                            player.position.y + 15),
                    player.clamped_direction,
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            bullet_list.back().speed *= 2;

        } else if (player.direction.y == 0.0f) {

            bullet_list.push_back(Bullet(
                    Vector2(player.position.x - 15, player.position.y + 3),
                    player.clamped_direction * (-1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 16,
                            player.position.y + 3),
                    player.clamped_direction,
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            bullet_list.back().speed *= 2;
        } else if (player.direction.y == -1.0f) {
            bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 4, player.position.y),
                    player.clamped_direction,
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            bullet_list.back().speed *= 2;

            bullet_list.push_back(Bullet(
                    Vector2(player.position.x - 12,
                            player.position.y + 15),
                    player.clamped_direction * (-1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));


        }
    } else if (player.direction.x == 0.0f) {

        if (player.direction.y == 1.0f) {
            bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 8, player.position.y - 15),
                    player.clamped_direction * (-1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 8, player.position.y + 16),
                    Vector2(0, 1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            bullet_list.back().speed *= 2;


        } else if (player.direction.y == -1.0f) {
            bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 3, player.position.y - 15),
                    player.clamped_direction,
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            bullet_list.back().speed *= 2;

            bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 3, player.position.y + 16),
                    player.clamped_direction * (-1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));


        }
    } else if (player.direction.x == -1.0f) {
        if (player.direction.y == 1.0f) {
            bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 11, player.position.y),
                    player.clamped_direction * (-1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale

            ));

            bullet_list.push_back(Bullet(
                    Vector2(player.position.x - 5,
                            player.position.y + 15),
                    player.clamped_direction,
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            bullet_list.back().speed *= 2;

        } else if (player.direction.y == 0.0f) {
            bullet_list.push_back(Bullet(
                    Vector2(player.position.x, player.position.y + 3),
                    player.clamped_direction,
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            bullet_list.back().speed *= 2;


            bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 16, player.position.y + 3),
                    player.clamped_direction * (-1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));


        } else if (player.direction.y == -1.0f) {

            bullet_list.push_back(Bullet(
                    Vector2(player.position.x, player.position.y),
                    player.clamped_direction,
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            bullet_list.back().speed *= 2;

            bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 16,
                            player.position.y + 15),
                    player.clamped_direction * (-1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
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

void BulletHandler::move_player_bullet(Player& player, QuadTree& quad_tree, float &delta)
{
    for(auto bullet = bullet_list.begin(); bullet != bullet_list.end();)
    {
        float border = 1000.0f;

        if(Vector2::distance(player.position, bullet->position) > border || bullet->state == State::EXPLODE)
        {
            bullet = bullet_list.erase(bullet);
        }
        else
        {

            if(bullet->speed != 1200 && bullet->clamped_direction == player.clamped_direction)
            {
                bullet->speed *= 2;
            }
            else if(bullet->speed == 1200 && bullet->clamped_direction != player.clamped_direction)
            {
                bullet->speed /= 2;
            }

            bullet->move(delta);
            quad_tree.insert(*bullet);

            ++bullet;
        }

    }

}