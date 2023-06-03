#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include "Game.hpp"

const int WINDOW_WIDTH = 800;  // largura janela
const int WINDOW_HEIGHT = 800; // altura janela

int maingame()
{
    Player player = Player();
    SDL_Init(SDL_INIT_EVERYTHING); // inicializa SDL

    // Cria janela
    SDL_Window *window = SDL_CreateWindow(
        "Tank Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);

    // renderizador
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // superficie e textura de imagem
    SDL_Surface *surface = SDL_LoadBMP("images/player01.bmp");
    player.texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_FreeSurface(surface);

    // Modificações da imagem
    player.rect.x = 300; // posição x
    player.rect.y = 300; // posição y
    player.rect.w = 100; // largura
    player.rect.h = 100; // altura

    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;

    double angle = 0.0;

    while (true)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {                               // identificar e reagir aos eventos
            if (event.type == SDL_QUIT) // sair do SDL
            {
                exit(0);
            }
            if(event.type == SDL_KEYUP){
                
                SDL_Keycode key = event.key.keysym.sym;
                player.dynamic.inMotion = !(key == SDLK_SPACE);

            }

            if (event.type == SDL_KEYDOWN)
            { // botões de movimento (A,S,D,W)
                SDL_Keycode key = event.key.keysym.sym;
                
                player.dynamic.inMotion = key == SDLK_SPACE;
            }
        }

        if(player.dynamic.inMotion){
            player.dynamic.Movement();
        }
        else{
            player.dynamic.angle += 1;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // deteca colisoẽs
        if (player.rect.x < 0)
        {
            std::cout << "bateu borda esqueda" << std::endl;
            moveLeft = false;
        }
        else if (player.rect.x + 100 > WINDOW_WIDTH) //+w devido ao comprimento da imagem
        {
            std::cout << "bateu borda direita" << std::endl;
            moveRight = false;
        }
        if (player.rect.y < 0)
        {
            std::cout << "bateu borda superior" << std::endl;
            moveUp = false;
        }
        else if (player.rect.y + 100 > WINDOW_HEIGHT) //+h devido ao comprimento da imagem
        {
            std::cout << "bateu borda inferior" << std::endl;
            moveDown = false;
        }

        SDL_RenderClear(renderer);

        SDL_RenderCopyEx(renderer, player.texture, NULL, &player.rect, player.dynamic.angle, NULL, SDL_FLIP_NONE);

        SDL_RenderPresent(renderer);

        SDL_Delay(25); // tempo de renderização
    }

    SDL_DestroyTexture(player.texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit; // fim

    return 0;
}