cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

project (turnbased_game)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set (CMAKE_CXX_STANDARD 11)
add_executable(turnbased_game Game.cpp tictactoe.cpp main.cpp)
