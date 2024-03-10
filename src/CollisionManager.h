#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include "CollisionCircle.h"



class CollisionManager
{
private:
    std::vector<CollisionCircle> collision_circles;

public:

    Vector2 scale = Vector2(4.0f, 4.0f);

    /**
     * Constructs a new CollisionManager object.
     */
    explicit CollisionManager();

    /**
     * Creates CollisionCircle instances and insert them in a collision circles list.
     */
    void create_collision_circles();

    /**
     * Retrieves the CollisionCircle instance representing a Player's collision.
     *
     * @return CollisionCircle instance representing a Player's collision.
     */
    CollisionCircle get_player_collision();

    /**
     * Retrieves the CollisionCircle instance representing an E Type Enemy's collision.
     *
     * @return CollisionCircle instance representing an E Type Enemy's collision.
     */
    CollisionCircle get_e_type_collision();

    /**
     * Retrieves the CollisionCircle instance representing an I Type Enemy's collision.
     *
     * @return CollisionCircle instance representing an I Type Enemy's collision.
     */
    CollisionCircle get_i_type_collision();

    /**
     * Retrieves the CollisionCircle instance representing an P Type Enemy's collision.
     *
     * @return CollisionCircle instance representing an P Type Enemy's collision.
     */
    CollisionCircle get_p_type_collision();

    /**
     * Retrieves the CollisionCircle instance representing a spy's collision.
     *
     * @return CollisionCircle instance representing a spy's collision.
     */
    CollisionCircle get_spy_collision();

    /**
     * Retrieves the CollisionCircle instance representing a mine's collision.
     *
     * @return CollisionCircle instance representing a mine's collision.
     */
    CollisionCircle get_mine_collision();

    /**
     * Retrieves the CollisionCircle instance representing an asteroid's collision.
     *
     * @return CollisionCircle instance representing an asteroid's collision.
     */
    CollisionCircle get_asteroid_collision();

    /**
     * Retrieves the CollisionCircle instance representing a mine explosion's collision.
     *
     * @return CollisionCircle instance representing a mine explosion's collision.
     */
    CollisionCircle get_mine_explosion_collision();

    /**
     * Retrieves the CollisionCircle instance representing a player bullet's collision.
     *
     * @return CollisionCircle instance representing a player bullet's collision.
     */
    CollisionCircle get_player_bullet_collision();

    /**
     * Retrieves the CollisionCircle instance representing an enemy bullet's collision.
     *
     * @return CollisionCircle instance representing an enemy bullet's collision.
     */
    CollisionCircle get_enemy_bullet_collision();

    /**
     * Retrieves Collision Circle instances representing the collision of a space station and its cannons.
     *
     * @return list of CollisionCircle instances representing the collision of a space station and its cannons.
     */
    std::vector<CollisionCircle> get_space_station_collisions();

};


#endif