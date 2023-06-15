#pragma once

#include <SDL.h>

class Object
{
public:
    int type;
    int group;
    bool destroy;
    SDL_FRect rect;

    Object(int t, int g) : type(t), group(g) {}

    bool CheckCollision(SDL_FRect collider)
    {
        return !(rect.y + rect.h <= collider.y ||
                 rect.y >= collider.y + collider.h ||
                 rect.x + rect.w <= collider.x ||
                 rect.x >= collider.x + collider.w);
    }

    bool CheckWindowLimits(int w_h, int w_w){
        return !(rect.x >= 0 && rect.y >= 0 &&
            rect.x + rect.w <= w_w && rect.y + rect.h <= w_h);
    }

    int *CollisionWall(){
        int *bounds = new int[4];
        bounds[0] = rect.x;
        bounds[1] = rect.x + rect.w;
        bounds[2] = rect.y;
        bounds[3] = rect.y + rect.h;
        return bounds;
    }

    virtual void CollisionEvent(int type) = 0;
};