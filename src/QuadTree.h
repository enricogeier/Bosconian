#ifndef QUADTREE_H
#define QUADTREE_H

#include <list>
#include <map>
#include <functional>
#include <iostream>
#include <cmath>
#include "Score.h"



class QuadTree
{
private:
    Rectangle boundary;
    short NODE_CAPACITY = 4;
    bool divided = false;
    std::list<std::reference_wrapper<GameObject>> game_objects;
    std::list<QuadTree> quad_trees;

    QuadTree* parent = nullptr;


    void subdivide();

    void check_collision_in_neighbour_tile(QuadTree* checked_quad, GameObject& gameObject, Vector2& border_position, Score& score);

    void do_collision_calculation(GameObject& game_object, Score& score);

    bool calculate_collision(CollisionCircle& huge_circle, CollisionCircle& small_circle);

public:
    explicit QuadTree(Rectangle boundary = {}, QuadTree* parent = nullptr): boundary(boundary), parent(parent){}

    void insert(GameObject& game_object);

    void check_collision(GameObject& game_object, Score& score);

};



#endif