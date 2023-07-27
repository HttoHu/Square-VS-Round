cmake_minimum_required(VERSION 3.10)
project(square_vs_round)
set(CMAKE_CXX_STANDARD 17)
include_directories("/usr/local/Cellar/sdl2_ttf/2.20.2/include/SDL2")
include_directories("/usr/local/Cellar/sdl2_image/2.6.3_1/include/SDL2")
include_directories("/usr/local/Cellar/sdl2/2.28.1/include/SDL2")

link_directories("/usr/local/Cellar/sdl2_ttf/2.20.2/lib")
link_directories("/usr/local/Cellar/sdl2_image/2.6.3_1/lib")
link_directories("/usr/local/Cellar/sdl2/2.28.1/lib")

link_libraries("SDL2")
link_libraries("SDL2main")
link_libraries("SDL2_test")
link_libraries("SDL2_ttf")
link_libraries("SDL2_image")

add_executable(
    square_vs_round
    ./libs/json_parser.cpp
    ./sources/bullet.cpp
    ./sources/def.cpp 
    ./sources/draw.cpp 
    ./sources/game.cpp 
    ./sources/game_input.cpp 
    ./sources/game_map.cpp 
    ./sources/init.cpp 
    ./sources/main.cpp 
    ./sources/objects.cpp 
    ./sources/player.cpp 
    ./sources/pos.cpp 
    ./sources/round.cpp 
    ./sources/smile.cpp 
    ./sources/square.cpp 
    ./sources/test.cpp 
    ./sources/UI.cpp 
    ./sources/utility.cpp 
    ./sources/widget.cpp 
)
