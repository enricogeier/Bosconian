#ifndef BULLETHANDLER_H
#define BULLETHANDLER_H

#include <list>
#include "Vector2.h"
#include "Bullet.h"
#include "QuadTree.h"
#include "Score.h"
#include "CollisionManager.h"
#include "Player.h"

class BulletHandler
{
private:
    std::list<Bullet> bullet_list;
    const float BORDER = 700.0f;

    const int ENEMY_BULLET_SPEED = 250;

public:
    float previous_player_speed = 0.0f;

    /**
     * Constructs a new BulletHandler object
     */
    BulletHandler() = default;

    /**
     * Inserts new player bullets for the bullet list.
     *
     * @param player reference to a Player object. Used to adjust Bullet properties
     * @param collision_manager reference to a CollisionManager object. Used for collision calculation
     */
    void insert_player_bullets(Player& player, CollisionManager& collision_manager);

    /**
     * Inserts new enemy bullets for the bullet list.
     *
     * @param position position used for bullet position
     * @param direction direction used for bullet direction
     * @param collision_manager reference to a CollisionManager object. Used for collision calculation
     */

    void insert_enemy_bullet(Vector2& position, Vector2& direction, CollisionManager& collision_manager);

    /**
     * Retrieves list containing Bullet instances used in game
     *
     * @return list containing Bullet instances used in game
     */
    std::list<Bullet> get_bullets() const;

    /**
     * Calls functions for collision calculation
     *
     * @param quad_tree A reference to a QuadTree object used for collision calculation
     * @param score A reference to a Score object used for updating the score values
     */
    void check_collisions(QuadTree& quad_tree, Score& score);

    /**
     * Removes all bullets in game
     */
    void clear_bullets();

    /**
     * Moves Bullets in game. Sets new position for each Bullet instance used in game
     *
     * @param player Reference to player instance used for setting bullet positions
     * @param quad_tree Reference to QuadTree object. Inserts bullets in the quad tree
     * @param delta Time between two frames
     */
    void move_bullets(Player& player, QuadTree& quad_tree, float& delta);

};

#endif