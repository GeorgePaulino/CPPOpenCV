#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <algorithm>

#include "Player.hpp"

class Player;

class Projetile : public Object
{
public:

    Player *player = NULL;
    SDL_Texture *texture = NULL;

    double angle = 0;
    float speed = 3;
    float impulse = 54;
    bool destroy = false;


    Projetile(Player *p, int pN, float x, float y, double angle, SDL_Renderer **renderer) : Object(1, pN), angle(angle)
    {
        player = p;
        texture = IMG_LoadTexture(*renderer, "images/projetile.png");
        
        if(pN == 0) SDL_SetTextureColorMod(texture, 150, 150, 255);
        else if(pN == 1) SDL_SetTextureColorMod(texture, 255, 150, 150);

        rect.w = 10;
        rect.h = 10;
        rect.x = x - 5;
        rect.y = y - 5;
        Impulse();
    }

    void Impulse()
    {
        double angle_rad = angle * M_PI / 180;
        rect.y += impulse * sin(angle_rad);
        rect.x += impulse * cos(angle_rad);
    }

    void Movement()
    {
        double angle_rad = angle * M_PI / 180;
        rect.y += speed * sin(angle_rad);
        rect.x += speed * cos(angle_rad);
    }

    void CollisionEvent(int type) override;
};