#include "QuadTree.h"

void QuadTree::subdivide()
{

    quad_trees.push_back(QuadTree(Rectangle{boundary.x, boundary.y, boundary.w / 2, boundary.h / 2}));
    quad_trees.push_back(QuadTree(Rectangle{boundary.x + boundary.w, boundary.y, boundary.w / 2, boundary.h / 2}));
    quad_trees.push_back(QuadTree(Rectangle{boundary.x, boundary.y + boundary.h, boundary.w / 2, boundary.h / 2}));
    quad_trees.push_back(QuadTree(Rectangle{boundary.x + boundary.w, boundary.y + boundary.h, boundary.w / 2, boundary.h / 2}));

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
            }
        }
    }

    game_objects.clear();

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
        if(game_objects.size() == 4)
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
    if(game_object.state == State::DESTROY)
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

        for(auto iterator = game_objects.begin(); iterator != game_objects.end(); ++iterator)
        {
            GameObject& object = *iterator;

            if(object.state == State::DESTROY)
            {
                continue;
            }

            // check collision for each object in quad
            if(std::find(game_object.collision_circle.can_collide_with.begin(),
                         game_object.collision_circle.can_collide_with.end(),
                         object.collision_circle.layer) !=
                         game_object.collision_circle.can_collide_with.end())
            {

                if(game_object.collision_circle.radius >=
                Vector2::distance(game_object.collision_circle.origin, object.collision_circle.origin))
                {

                    std::cout << "collision detected" << std::endl;


                    game_object.state = State::DESTROY;
                    object.state = State::DESTROY;

                    return;

                }
            }
        }


    }
}