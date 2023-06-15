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

class Projetile;

#define P_W 75
#define P_H 75

class Player : public Object
{
public:
    int player = 0;

    std::vector<Player *> *players = NULL;

    std::vector<Projetile *> projetiles;
    std::vector<Object *> *objects = NULL;
    SDL_Texture *texture = NULL;
    SDL_KeyCode key;
    SDL_Renderer **renderer = NULL;

    int backward = 0;
    double angle = 0;

    Player(int p, std::vector<Object *> *objects, SDL_Renderer **renderer, std::vector<Player *> *ps) : Object(0, p), player(p), objects(objects), renderer(renderer)
    {
        players = ps;
        if (p == 0)
        {
            rect.x = 100;
            rect.y = 350;
            rect.w = P_W;
            rect.h = P_H;
            key = SDLK_SPACE;
            texture = IMG_LoadTexture(*renderer, "images/tank1.png");
        }
        else if (p == 1)
        {
            rect.x = 700;
            rect.y = 350;
            rect.w = P_W;
            rect.h = P_H;
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
            if (!inMotion && !kUp)
            {
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

        if (backward)
        {
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

    void Fire();

    void CollisionEvent(int type) override
    {
        if (type == 1)
        {
            players->erase(players->begin() + player);
        }
        else
        {
            backward = 30;
        }
        destroy = true;
    }

private:
    bool inMotion = false;
    float speed = 1;
};
