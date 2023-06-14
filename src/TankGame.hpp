#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <vector>

#include "Game/Player.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

class Field
{
public:
    std::vector<Object *> objects;
    std::vector<Player *> players;
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    SDL_Texture *background = NULL;
    SDL_Rect rect;

    Field()
    {
        // Initializing
        SDL_Init(SDL_INIT_EVERYTHING);
        IMG_Init(IMG_INIT_PNG);

        window = SDL_CreateWindow(
            "Tank Game",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH, WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Loading Texture

        background = IMG_LoadTexture(renderer, "images/bg.png");
        rect.x = 0;
        rect.y = 0;
        rect.h = 800;
        rect.w = 800;

        // Adding Players
        players.push_back(new Player(0, &renderer));
        players.push_back(new Player(1, &renderer));

        for(auto player : players){
            objects.push_back(player);
        }

        //
    }

    ~Field()
    {
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Loop()
    {
        while (true)
        {
            Events();
            SDL_RenderClear(renderer);
            SDL_RenderCopyF(renderer, background, &rect, NULL);
            for(auto player: players){
                SDL_RenderCopyExF(renderer, player->texture, NULL, &player->rect, player->angle, NULL, SDL_FLIP_NONE);
                for(auto projetile: player->projetiles){
                    SDL_RenderCopyExF(renderer, projetile->texture, NULL, &projetile->rect, projetile->angle, NULL, SDL_FLIP_NONE);
                }
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(25);
        }
    }

    void Events()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // Close
            if (event.type == SDL_QUIT)
            {
                exit(0);
            }

            // Key Up

            if(event.type == SDL_KEYUP){
                SDL_Keycode key = event.key.keysym.sym;
                for(auto player : players){
                    player->InMotionCheck(key, true);
                }
            }

            // Key Pressed

            if (event.type == SDL_KEYDOWN)
            {
                SDL_Keycode key = event.key.keysym.sym;
                for(auto player : players){
                    player->InMotionCheck(key, false);
                }
            }
        }

        for(auto player: players){
            player->Movement();
            if(player->CheckWindowLimits(WINDOW_HEIGHT, WINDOW_WIDTH))
                player->CollisionEvent(-1);
            for(auto projetile: player->projetiles){
                projetile->Movement();
            }
        }
    }
};

int maingame()
{
    Field field = Field();
    field.Loop();
    return 0;
}