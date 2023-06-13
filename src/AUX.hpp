/**
 * @file AUX.cpp
 * @brief File with some helper classes.
 *
 */

#pragma once

#include <SDL.h>
#include <math.h>

/// @brief Movement of the object.
class Dynamic
{
public:
    SDL_Rect *rect;

    bool inMotion;
    float speed = 1;
    double angle = 0;

    Dynamic(SDL_Rect *rect) : rect(rect) {}

    void Collision()
    {
        // deteca colisoẽs
        /*if (rect.x < 0)
        {
            rect.x = 1;
        }
        else if (rect.x + 100 > WINDOW_WIDTH) //+w devido ao comprimento da imagem
        {
            moveRight = false;
        }
        if (rect.y < 0)
        {
            moveUp = false;
        }
        else if (player.rect.y + 100 > WINDOW_HEIGHT) //+h devido ao comprimento da imagem
        {
            moveDown = false;
        }*/
    }

    void Movement()
    {
        double angle_rad = (angle + 180)* M_PI / 180;
        rect->y += speed * sin(angle_rad);
        rect->x += speed * cos(angle_rad);
        std::cout << speed * angle << std::endl;
        std::cout << speed * sin(angle_rad) << std::endl;
        std::cout << speed * cos(angle_rad) << std::endl;
        std::cout << "OSHOISDISHFOSDF" << std::endl;
    }

        void fire(SDL_Renderer* renderer)
    {   
        int x, y = 0;

        x = y = +10;

        SDL_Rect rectf;
        rectf.h = rectf.w = 10;
        rectf.x = rect->x + x;
        rectf.y = rect->y + y;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  //vermelho
        SDL_RenderFillRect(renderer, &rectf);
        SDL_RenderPresent(renderer);
    }

};
