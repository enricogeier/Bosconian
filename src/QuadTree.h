#ifndef QUADTREE_H
#define QUADTREE_H

#include <list>
#include <functional>
#include <iostream>
#include "GameObject.h"



class QuadTree
{
private:
    Rectangle boundary;
    static const short NODE_CAPACITY = 4;
    bool divided = false;
    std::list<std::reference_wrapper<GameObject>> game_objects;
    std::list<QuadTree> quad_trees;

    void subdivide();

public:
    explicit QuadTree(Rectangle boundary = {}): boundary(boundary){}

    void insert(GameObject& game_object);

    void check_collision(GameObject& game_object);

};



#endif
