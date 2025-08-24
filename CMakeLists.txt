cmake_minimum_required(VERSION 3.22)
project(rocketz)

set(CMAKE_C_STANDARD 11)

add_executable(rocketz src/main.c src/game_loop.c)
target_link_libraries(rocketz ncurses)