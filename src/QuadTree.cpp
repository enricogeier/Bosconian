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

void QuadTree::check_collision_in_neighbour_tile(QuadTree *checked_quad, GameObject &game_object, Vector2& border_position)
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
                    quad.check_collision_in_neighbour_tile(nullptr, game_object, border_position);
                }
                else
                {
                    quad.do_collision_calculation(game_object);
                }

                return;
            }
        }
    }

    if(parent != nullptr)
    {
        parent->check_collision_in_neighbour_tile(this, game_object, border_position);
    }




}

void QuadTree::do_collision_calculation(GameObject &game_object)
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

            float max_radius = game_object.collision_circle.radius > object.collision_circle.radius ? game_object.collision_circle.radius : object.collision_circle.radius;
            if(max_radius >=
               Vector2::distance(game_object.collision_circle.origin, object.collision_circle.origin))
            {

                if(game_object.type == Type::MINE || game_object.type == Type::CANNON)
                {
                    if(game_object.state == State::NORMAL)
                    {
                        game_object.state = State::EXPLODE;
                    }

                    object.state = State::EXPLODE;
                }
                else if(object.type == Type::MINE || object.type == Type::CANNON)
                {
                    if(object.state == State::NORMAL)
                    {
                        object.state = State::EXPLODE;
                    }

                    game_object.state = State::EXPLODE;
                }
                else
                {
                    game_object.state = State::EXPLODE;
                    object.state = State::EXPLODE;
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

void QuadTree::check_collision(GameObject &game_object)
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
                quad.check_collision(game_object);
            }
        }
    }
    else
    {

        do_collision_calculation(game_object);


        // no collision found, check if game object is near border of quad
        if(parent != nullptr)
        {
            if(game_object.collision_circle.origin.x + game_object.collision_circle.radius >= boundary.x + boundary.w)
            {
                Vector2 border_position{
                    game_object.collision_circle.origin.x +  game_object.collision_circle.radius,
                        game_object.collision_circle.origin.y
                };
                parent->check_collision_in_neighbour_tile(this, game_object, border_position);
            }
            else if(game_object.collision_circle.origin.x - game_object.collision_circle.radius <= boundary.x)
            {
                Vector2 border_position{
                        game_object.collision_circle.origin.x - game_object.collision_circle.radius,
                        game_object.collision_circle.origin.y
                };
                parent->check_collision_in_neighbour_tile(this, game_object, border_position);
            }
            else if(game_object.collision_circle.origin.y + game_object.collision_circle.radius >= boundary.y + boundary.h)
            {
                Vector2 border_position{
                    game_object.collision_circle.origin.x,
                    game_object.collision_circle.origin.y + game_object.collision_circle.radius
                };

                parent->check_collision_in_neighbour_tile(this, game_object, border_position);
            }
            else if(game_object.collision_circle.origin.y - game_object.collision_circle.radius <= boundary.y)
            {
                Vector2 border_position{
                        game_object.collision_circle.origin.x,
                        game_object.collision_circle.origin.y - game_object.collision_circle.radius
                };

                parent->check_collision_in_neighbour_tile(this, game_object, border_position);
            }


        }
    }
}