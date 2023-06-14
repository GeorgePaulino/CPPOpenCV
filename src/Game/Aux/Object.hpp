#include <SDL.h>

class Object
{
public:
    int type;
    SDL_FRect rect;

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

    virtual void CollisionEvent(int type) = 0;
};