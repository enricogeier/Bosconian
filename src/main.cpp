#include "GameHandler.h"
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    GameHandler game_handler;
    game_handler.run();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
