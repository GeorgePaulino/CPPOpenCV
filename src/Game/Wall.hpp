#pragma once

#include <SDL.h>
#include <vector>

#include "Aux/Object.hpp"

class Wall : public Object{
public:
    std::vector<Wall *> *walls = NULL;

    Wall(int x, int y, std::vector<Wall *> * ws) : Object(2, -1){
        walls = ws;
        rect.w = 1;
        rect.h = 1;
        rect.x = x;
        rect.y = y;
    }

    void CollisionEvent(int type) override{
        if(type == 1){
            auto it = std::find(walls->begin(), walls->end(), this);
            walls->erase(it);
            destroy = true;
        }
    }
};