cmake_minimum_required(VERSION 3.10)
project(Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(GTest REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})



set(CMAKE_CXX_STANDARD 17)

set(googletest FALSE)
if(googletest)
    add_executable(Test
            test/mainTest.cpp
            test/BulletTest.cpp
            src/Player.h
            src/Player.cpp
            src/Vector2.h
            src/Vector2.cpp
            src/GameHandler.h
            src/GameHandler.cpp
            src/Renderer.h
            src/Renderer.cpp
            src/Timer.h
            src/Timer.cpp
            src/FPSTimer.h
            src/FPSTimer.cpp
            src/Input.h
            src/Input.cpp
            src/Tile.h
            src/Tile.cpp
            src/Level.h
            src/Level.cpp
            src/Rectangle.h
            src/GameObject.h
            src/Enemy.h
            src/Enemy.cpp
            src/Bullet.h
            src/QuadTree.h
            src/QuadTree.cpp
            src/CollisionCircle.h
            src/CollisionManager.h
            src/CollisionManager.cpp
            src/Bullet.cpp
            src/GameObject.cpp
            src/BulletHandler.h
            src/BulletHandler.cpp
            src/Mine.h
            src/Mine.cpp
            src/SpaceStation.h
            src/Cannon.h
            src/SpaceStation.cpp
            src/Cannon.cpp
            src/Score.h
            src/Score.cpp
            src/Sound.h
            src/Sound.cpp
    )
else ()
    add_executable(Test src/main.cpp
            src/Player.h
            src/Player.cpp
            src/Vector2.h
            src/Vector2.cpp
            src/GameHandler.h
            src/GameHandler.cpp
            src/Renderer.h
            src/Renderer.cpp
            src/Timer.h
            src/Timer.cpp
            src/FPSTimer.h
            src/FPSTimer.cpp
            src/Input.h
            src/Input.cpp
            src/Tile.h
            src/Tile.cpp
            src/Level.h
            src/Level.cpp
            src/Rectangle.h
            src/GameObject.h
            src/Enemy.h
            src/Enemy.cpp
            src/Bullet.h
            src/QuadTree.h
            src/QuadTree.cpp
            src/CollisionCircle.h
            src/CollisionManager.h
            src/CollisionManager.cpp
            src/Bullet.cpp
            src/GameObject.cpp
            src/BulletHandler.h
            src/BulletHandler.cpp
            src/Mine.h
            src/Mine.cpp
            src/SpaceStation.h
            src/Cannon.h
            src/SpaceStation.cpp
            src/Cannon.cpp
            src/Score.h
            src/Score.cpp
            src/Sound.h
            src/Sound.cpp

    )
endif ()





# Link against SDL2
target_link_libraries(Test ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${GTEST_LIBRARIES})
