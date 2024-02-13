#include "QuadTree.h"

void QuadTree::subdivide()
{

    quad_trees.push_back(QuadTree(Rectangle{boundary.x, boundary.y, boundary.w / 2, boundary.h / 2}, this));
    quad_trees.push_back(QuadTree(Rectangle{boundary.x + (boundary.w / 2), boundary.y, boundary.w / 2, boundary.h / 2}, this));
    quad_trees.push_back(QuadTree(Rectangle{boundary.x, boundary.y + (boundary.h / 2), boundary.w / 2, boundary.h / 2}, this));
    quad_trees.push_back(QuadTree(Rectangle{boundary.x + (boundary.w / 2), boundary.y + (boundary.h / 2), boundary.w / 2, boundary.h / 2}, this));

    for(GameObject& object : game_objects)
    {
        for(auto& quad : quad_trees)
        {
            if(
                    object.position.x < quad.boundary.x + quad.boundary.w &&
                    object.position.x >= quad.boundary.x &&
                    object.position.y < quad.boundary.y + quad.boundary.h &&
                    object.position.y >= quad.boundary.y
                    )
            {
                quad.insert(object);
                break;
            }
        }
    }

    game_objects.clear();

}

void QuadTree::check_collision_in_neighbour_tile(QuadTree *checked_quad, GameObject &game_object, Vector2& border_position, Score& score)
{
    for(auto& quad : quad_trees)
    {
        if(checked_quad != &quad)
        {
            if
                    (
                    border_position.x < quad.boundary.x + quad.boundary.w &&
                    border_position.x >= quad.boundary.x &&
                    border_position.y < quad.boundary.y + quad.boundary.h &&
                    border_position.y >= quad.boundary.y
                    )
            {
                if(quad.divided)
                {
                    quad.check_collision_in_neighbour_tile(nullptr, game_object, border_position, score);
                }
                else
                {
                    quad.do_collision_calculation(game_object, score);
                }

                return;
            }
        }
    }

    if(parent != nullptr)
    {
        parent->check_collision_in_neighbour_tile(this, game_object, border_position, score);
    }




}

void QuadTree::do_collision_calculation(GameObject &game_object, Score& score)
{
    for(auto iterator = game_objects.begin(); iterator != game_objects.end(); ++iterator)
    {
        GameObject& object = *iterator;

        if(object.state == State::EXPLODE && object.type != Type::MINE)
        {
            continue;
        }

        // check collision for each object in quad
        if(std::find(game_object.collision_circle.can_collide_with.begin(),
                     game_object.collision_circle.can_collide_with.end(),
                     object.collision_circle.layer) !=
           game_object.collision_circle.can_collide_with.end())
        {

            bool collision = false;

            if(game_object.collision_circle.radius > object.collision_circle.radius)
            {
                collision = calculate_collision(game_object.collision_circle, object.collision_circle);
            }
            else
            {
                collision = calculate_collision(object.collision_circle, game_object.collision_circle);
            }

            if(collision)
            {

                if(game_object.type == Type::MINE || game_object.type == Type::CANNON)
                {
                    if(game_object.state == State::NORMAL)
                    {
                        game_object.state = State::EXPLODE;
                    }

                    object.state = State::EXPLODE;

                    if(game_object.type == Type::CANNON && object.type == Type::PLAYER)
                    {
                        game_object.state = State::PLAYER_COLLISION;
                    }

                }
                else if(object.type == Type::MINE || object.type == Type::CANNON)
                {
                    if(object.state == State::NORMAL)
                    {
                        object.state = State::EXPLODE;
                    }

                    game_object.state = State::EXPLODE;

                    if(object.type == Type::CANNON && game_object.type == Type::PLAYER)
                    {
                        object.state = State::PLAYER_COLLISION;
                    }

                }
                else
                {
                    game_object.state = State::EXPLODE;
                    object.state = State::EXPLODE;
                }


                if(game_object.type != Type::PLAYER && game_object.type != Type::BULLET)
                {
                    score.increase_score(game_object.type);
                }
                if(object.type != Type::PLAYER && object.type != Type::BULLET)
                {
                    score.increase_score(object.type);
                }


                return;

            }
        }
    }
}



void QuadTree::insert(GameObject& game_object)
{
    if(divided)
    {
        for(auto& quad : quad_trees)
        {
            if(
                    game_object.position.x < quad.boundary.x + quad.boundary.w &&
                    game_object.position.x >= quad.boundary.x &&
                    game_object.position.y < quad.boundary.y + quad.boundary.h &&
                    game_object.position.y >= quad.boundary.y
                    )
            {
                quad.insert(game_object);
            }
        }
    }
    else
    {
        if(game_objects.size() == NODE_CAPACITY)
        {
            subdivide();
            divided = true;
            this->insert(game_object);
        }
        else
        {
            game_objects.push_back(game_object);
        }
    }
}

void QuadTree::check_collision(GameObject &game_object, Score& score)
{
    if(game_object.state == State::EXPLODE && game_object.type != Type::MINE)
    {
        return;
    }
    else if(divided)
    {
        for(auto& quad : quad_trees)
        {
            if(
                    game_object.position.x < quad.boundary.x + quad.boundary.w &&
                    game_object.position.x >= quad.boundary.x &&
                    game_object.position.y < quad.boundary.y + quad.boundary.h &&
                    game_object.position.y >= quad.boundary.y
                    )
            {
                quad.check_collision(game_object, score);
            }
        }
    }
    else
    {

        do_collision_calculation(game_object, score);


        // no collision found, check if game object is near border of quad
        if(parent != nullptr)
        {
            if(game_object.collision_circle.origin.x + game_object.collision_circle.radius >= boundary.x + boundary.w)
            {
                Vector2 border_position{
                        game_object.collision_circle.origin.x +  game_object.collision_circle.radius,
                        game_object.collision_circle.origin.y
                };
                parent->check_collision_in_neighbour_tile(this, game_object, border_position, score);
            }
            else if(game_object.collision_circle.origin.x - game_object.collision_circle.radius <= boundary.x)
            {
                Vector2 border_position{
                        game_object.collision_circle.origin.x - game_object.collision_circle.radius,
                        game_object.collision_circle.origin.y
                };
                parent->check_collision_in_neighbour_tile(this, game_object, border_position, score);
            }
            else if(game_object.collision_circle.origin.y + game_object.collision_circle.radius >= boundary.y + boundary.h)
            {
                Vector2 border_position{
                        game_object.collision_circle.origin.x,
                        game_object.collision_circle.origin.y + game_object.collision_circle.radius
                };

                parent->check_collision_in_neighbour_tile(this, game_object, border_position, score);
            }
            else if(game_object.collision_circle.origin.y - game_object.collision_circle.radius <= boundary.y)
            {
                Vector2 border_position{
                        game_object.collision_circle.origin.x,
                        game_object.collision_circle.origin.y - game_object.collision_circle.radius
                };

                parent->check_collision_in_neighbour_tile(this, game_object, border_position, score);
            }


        }
    }
}

bool QuadTree::calculate_collision(CollisionCircle &huge_circle, CollisionCircle &small_circle)
{
    float max_radius = huge_circle.radius;
    Vector2 origin = small_circle.origin;
    Vector2 start_origin = huge_circle.origin;
    float radius = small_circle.radius;




    Vector2 north = Vector2(origin.x, origin.y - radius);
    Vector2 east = Vector2(origin.x + radius, origin.y);
    Vector2 south = Vector2(origin.x, origin.y + radius);
    Vector2 west = Vector2(origin.x - radius, origin.y);

    if(
            max_radius >= Vector2::distance(start_origin, north)
            || max_radius >= Vector2::distance(start_origin, east)
            || max_radius >= Vector2::distance(start_origin, south)
            || max_radius >= Vector2::distance(start_origin, west)
            )
    {
        return true;
    }
    else
    {
        return false;
    }


}