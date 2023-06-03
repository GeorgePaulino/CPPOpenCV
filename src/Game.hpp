/**
 * @file Game.cpp
 * @brief Files useds in the game.
 */

#pragma once

#include<vector>

#include "AUX.hpp"

class Field{
    Field(){
    }
    Game::Size size = Game::Size(600, 600);
    std::vector<Game::Position> spawners;
};

class Spawn{
public:
    int player;
    Game::Position position;
};