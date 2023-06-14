/**
 * @file Game.cpp
 * @brief Files useds in the game.
 */

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <math.h>

#include "Aux/Object.hpp"
#include "Projetile.hpp"

class Player : public Object
{
public:
    int player = 0;

    std::vector<Projetile *> projetiles;
    SDL_Texture *texture = NULL;
    SDL_KeyCode key;
    SDL_Renderer **renderer = NULL;

    int backward = 0;
    double angle = 0;

    Player(int p, SDL_Renderer **renderer) : player(p), renderer(renderer)
    {
        type = 0;
        if (p == 0)
        {
            rect.x = 300;
            rect.y = 300;
            rect.w = 100;
            rect.h = 52;
            key = SDLK_SPACE;
            texture = IMG_LoadTexture(*renderer, "images/tank1.png");
        }
        else if (p == 1)
        {
            rect.x = 50;
            rect.y = 50;
            rect.w = 100;
            rect.h = 52;
            key = SDLK_0;
            texture = IMG_LoadTexture(*renderer, "images/tank2.png");
        }
    }

    ~Player()
    {
        SDL_DestroyTexture(texture);
    }

    void InMotionCheck(SDL_Keycode k, bool kUp)
    {

        if (key == k)
        {
            if(!inMotion && !kUp){
                Fire();
            }
            inMotion = !kUp;
        }
    }

    void Movement()
    {
        double angle_rad = angle * M_PI / 180;
        float yD = speed * sin(angle_rad);
        float xD = speed * cos(angle_rad);

        if(backward){
            rect.y -= yD;
            rect.x -= xD;
            backward--;
        }
        else if (inMotion)
        {
            rect.y += yD;
            rect.x += xD;
        }
        else
        {
            angle += 1;
        }
    }

    void Fire(){
        projetiles.push_back(new Projetile(player, rect.x + rect.w / 2, rect.y + rect.h / 2, angle, renderer));
    }

    void CollisionEvent(int type) override {
        if(type == 1){

        }
        else{
            backward = 30;
        }
    }


private:
    bool inMotion = false;
    float speed = 1;
};
