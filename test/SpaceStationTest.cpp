#include "../src/SpaceStation.h"
#include "../src/CollisionManager.h"
#include <gtest/gtest.h>

TEST(SpaceStation, update_cannon_positions)
{
    CollisionManager collisionManager;

    SpaceStation spaceStation = SpaceStation(
            Vector2(),
            collisionManager.get_space_station_collisions(),
            collisionManager.scale
            );


    std::vector<Vector2> previousPositions;

    for(auto& cannon : spaceStation.cannons)
    {
        previousPositions.push_back(cannon.position);
    }

    Vector2 offset = Vector2(17.0f, 17.0f);
    spaceStation.update_cannon_positions(offset);

    {
        int i = 0;
        for(auto& position : previousPositions)
        {
            EXPECT_NE(position, spaceStation.cannons[i++].position);
        }
    }




}

TEST(SpaceStation, update_cannons)
{

}

TEST(SpaceStation, get_amount_of_cannons)
{

}
