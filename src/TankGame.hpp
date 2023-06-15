#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <vector>

#include "Game/Player.hpp"
#include "Game/Wall.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

class Field
{
public:
    std::vector<Object *> objects;
    std::vector<Wall *> walls;
    std::vector<Player *> players;
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    SDL_Texture *background = NULL;
    SDL_Rect rect;
    int **field = NULL;

    Field(int **f) : field(f)
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
        players.push_back(new Player(0, &objects, &renderer, &players));
        players.push_back(new Player(1, &objects, &renderer, &players));

        for (auto player : players)
        {
            objects.push_back(player);
        }

        // Adding Walls
        
        for(int x = 0; x < 800; x++){
            for(int y = 0; y < 800; y++){
                if(f[x][y] == 1){
                    Wall *w = new Wall(x, y, &walls);
                    walls.push_back(w);
                }
            }
        }
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
            for (auto player : players)
            {
                if(player == nullptr) continue;
                SDL_RenderCopyExF(renderer, player->texture, NULL, &player->rect, player->angle, NULL, SDL_FLIP_NONE);
                for (auto projetile : player->projetiles)
                {
                    SDL_RenderCopyExF(renderer, projetile->texture, NULL, &projetile->rect, projetile->angle, NULL, SDL_FLIP_NONE);
                }
            }
            for(int x = 0; x < 800; x++){
                for(int y = 0; y < 800; y++){
                    if(field[x][y] == 1){
                        SDL_RenderDrawPoint(renderer, x, y);
                    }
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

            if (event.type == SDL_KEYUP)
            {
                SDL_Keycode key = event.key.keysym.sym;
                for (auto player : players)
                {
                    player->InMotionCheck(key, true);
                }
            }

            // Key Pressed

            if (event.type == SDL_KEYDOWN)
            {
                SDL_Keycode key = event.key.keysym.sym;
                for (auto player : players)
                {
                    player->InMotionCheck(key, false);
                }
            }
        }

        for (auto player : players)
        {
            player->Movement();
            if (player->CheckWindowLimits(WINDOW_HEIGHT, WINDOW_WIDTH))
                player->CollisionEvent(-1);
            for (auto projetile : player->projetiles)
            {
                projetile->Movement();
                if (projetile->CheckWindowLimits(WINDOW_HEIGHT, WINDOW_WIDTH))
                {
                    projetile->CollisionEvent(0);
                }
            }
        }

        for (int i = 0; i < objects.size() - 1; i++)
        {
            for (int j = i + 1; j < objects.size(); j++)
            {
                if (objects[i]->CheckCollision(objects[j]->rect) && (objects[i]->group != objects[j]->group))
                {
                    std::cout << "Objects " << objects.size()
                              << " ( " << i << ", " << j << " ) "
                              << " ( " << objects[i]->type << " , " << objects[j]->type << " ) "
                              << std::endl;

                    objects[i]->CollisionEvent(objects[j]->type);
                    objects[j]->CollisionEvent(objects[i]->type);
                    if (objects[i]->destroy)
                    {
                        objects.erase(objects.begin() + i);
                        objects.resize(objects.size() - 1);
                    }
                    if (objects[j]->destroy)
                    {
                        objects.erase(objects.begin() + j);
                        objects.resize(objects.size() - 1);
                    }
                }
                int *bs = objects[i]->CollisionWall();
                int q = 0;
                for(int x = bs[0]; x < bs[1]; x++){
                    for(int y = bs[2]; y < bs[3]; y++){
                        if(x < 0 || y < 0 || x >= 800 || y >= 800) continue;
                        if(field[x][y] == 1){
                            q++;
                            field[x][y] = 0;
                            if(objects[i]->type == 1 && q >= 15){
                                q = 0;
                                objects[i]->CollisionEvent(2);
                            }
                            //objects[i]->CollisionEvent(objects[j]->type);
                            
                        }
                    }
                }
            }
        }

        if (players.size() == 1)
        {
            std::cout << "DEATH" << std::endl;
        }
    }
};

int maingame(int** f)
{
    Field *field = new Field(f);
    field->Loop();
    delete field;
    return 0;
}