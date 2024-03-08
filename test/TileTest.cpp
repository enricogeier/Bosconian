#include "../src/Tile.h"
#include <gtest/gtest.h>

TEST(Tile, isObjectWithinTile)
{
    Tile tile = Tile(Vector2());

    Vector2 pos1 = Vector2(17.0f, 17.0f);
    Vector2 pos2 = Vector2(1000.0f, 1000.0f);

    EXPECT_TRUE(tile.is_object_within_tile(pos1, Vector2(100.0f, 100.0f)));
    EXPECT_FALSE(tile.is_object_within_tile(pos2, Vector2(100.0f, 100.0f)));

}

TEST(Tile, insertObject)
{
    Tile tile;
    Mine mine = Mine(Vector2(), CollisionCircle());
    GameObject gameObject = GameObject(Vector2(), CollisionCircle(), Type::E_TYPE);

    tile.insert_object(mine);
    tile.insert_object(mine);

    tile.insert_object(gameObject);
    tile.insert_object(gameObject);

    EXPECT_EQ(1, tile.mines.size());
    EXPECT_EQ(1, tile.objects.size());


}

TEST(Tile, updateTilePosition)
{
    Tile tile;
    Mine mine = Mine(Vector2(), CollisionCircle());

    tile.insert_object(mine);

    tile.tile_position = Vector2(-100.0f);

    tile.update_tile_position();

    EXPECT_EQ(Vector2(-100.0f, -100.0f), tile.mines.front().position);

}