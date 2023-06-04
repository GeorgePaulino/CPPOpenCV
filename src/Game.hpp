/**
 * @file Game.cpp
 * @brief Files useds in the game.
 */

#pragma once

#include<vector>

#include "AUX.hpp"

class Spawn{
public:
    int player;
};

class Field{
    Field() {}
    std::vector<Spawn> spawners;
};

class Player{
public:
    SDL_Texture* texture;
    SDL_Rect rect;
    Dynamic dynamic = Dynamic(&rect);
};