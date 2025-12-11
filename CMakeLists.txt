cmake_minimum_required(VERSION 4.0)
project(untitled12)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled12 main.cpp
        BoardGame_Classes.h
        Game1_SUS.h
        Game2_FourInRow.h
        Game3_5x5TicTacToe.h
        Game4_WordTicTacToe.h
        Game5_Misere.h
        Game6_Diamond.h
        Game7_4x4TicTacToe.h
        Game8_Pyramid.h
        Game9_Numerical.h
        Game10_Obstacles.h
        Game11_Infinity.h
        Game12_Memory.h
        AI_Players.h
)
