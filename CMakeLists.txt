cmake_minimum_required(VERSION 3.10)
project(Test)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

add_executable(Test src/main.cpp)

# Link against SDL2
target_link_libraries(Test ${SDL2_LIBRARIES})
