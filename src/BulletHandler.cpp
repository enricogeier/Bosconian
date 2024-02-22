#include "BulletHandler.h"

void BulletHandler::insert_enemy_bullet(Vector2 &position, Vector2& direction, CollisionManager &collision_manager)
{
    enemy_bullet_list.push_back(Bullet(
            position,
            direction,
            collision_manager.get_enemy_bullet_collision(),
            collision_manager.scale,
            300
    ));
}

void BulletHandler::insert_player_bullets(Player& player, CollisionManager& collision_manager) {
    if (player.direction.x == 1.0f) {
        if (player.direction.y == 1.0f) {
            player_bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 5, player.position.y),
                    player.clamped_direction * (-1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            player_bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 21,
                            player.position.y + 15),
                    player.clamped_direction,
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            player_bullet_list.back().speed *= 2;

        } else if (player.direction.y == 0.0f) {

            player_bullet_list.push_back(Bullet(
                    Vector2(player.position.x - 15, player.position.y + 3),
                    player.clamped_direction * (-1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            player_bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 16,
                            player.position.y + 3),
                    player.clamped_direction,
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            player_bullet_list.back().speed *= 2;
        } else if (player.direction.y == -1.0f) {
            player_bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 4, player.position.y),
                    player.clamped_direction,
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            player_bullet_list.back().speed *= 2;

            player_bullet_list.push_back(Bullet(
                    Vector2(player.position.x - 12,
                            player.position.y + 15),
                    player.clamped_direction * (-1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));


        }
    } else if (player.direction.x == 0.0f) {

        if (player.direction.y == 1.0f) {
            player_bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 8, player.position.y - 15),
                    player.clamped_direction * (-1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            player_bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 8, player.position.y + 16),
                    Vector2(0, 1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            player_bullet_list.back().speed *= 2;


        } else if (player.direction.y == -1.0f) {
            player_bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 3, player.position.y - 15),
                    player.clamped_direction,
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            player_bullet_list.back().speed *= 2;

            player_bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 3, player.position.y + 16),
                    player.clamped_direction * (-1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));


        }
    } else if (player.direction.x == -1.0f) {
        if (player.direction.y == 1.0f) {
            player_bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 11, player.position.y),
                    player.clamped_direction * (-1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale

            ));

            player_bullet_list.push_back(Bullet(
                    Vector2(player.position.x - 5,
                            player.position.y + 15),
                    player.clamped_direction,
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            player_bullet_list.back().speed *= 2;

        } else if (player.direction.y == 0.0f) {
            player_bullet_list.push_back(Bullet(
                    Vector2(player.position.x, player.position.y + 3),
                    player.clamped_direction,
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            player_bullet_list.back().speed *= 2;


            player_bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 16, player.position.y + 3),
                    player.clamped_direction * (-1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));


        } else if (player.direction.y == -1.0f) {

            player_bullet_list.push_back(Bullet(
                    Vector2(player.position.x, player.position.y),
                    player.clamped_direction,
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));

            player_bullet_list.back().speed *= 2;

            player_bullet_list.push_back(Bullet(
                    Vector2(player.position.x + 16,
                            player.position.y + 15),
                    player.clamped_direction * (-1),
                    collision_manager.get_player_bullet_collision(),
                    collision_manager.scale
            ));



        }
    }
}

std::list<Bullet> BulletHandler::get_player_bullets() const
{
    return this->player_bullet_list;
}

std::list<Bullet> BulletHandler::get_enemy_bullets() const
{
    return this->enemy_bullet_list;
}

void BulletHandler::check_collisions(QuadTree &quad_tree, Score& score)
{
    for(auto& bullet : player_bullet_list)
    {
        quad_tree.check_collision(bullet, score);
    }
    for(auto& bullet : enemy_bullet_list)
    {
        quad_tree.check_collision(bullet, score);
    }
}

void BulletHandler::move_bullets(Player& player, QuadTree& quad_tree, float &delta)
{
    for(auto bullet = player_bullet_list.begin(); bullet != player_bullet_list.end();)
    {


        if(Vector2::distance(player.position, bullet->position) > BORDER|| bullet->state == State::EXPLODE)
        {
            bullet = player_bullet_list.erase(bullet);
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
    for(auto bullet = enemy_bullet_list.begin(); bullet != enemy_bullet_list.end();)
    {


        if(Vector2::distance(player.position, bullet->position) > BORDER|| bullet->state == State::EXPLODE)
        {
            bullet = player_bullet_list.erase(bullet);
        }
        else
        {

            bullet->move(delta);
            quad_tree.insert(*bullet);

            ++bullet;
        }

    }

}


void BulletHandler::clear_bullets()
{
    player_bullet_list.clear();
    enemy_bullet_list.clear();
}