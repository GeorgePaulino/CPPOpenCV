#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <stdio.h>

const double ROTATION_SPEED = 90.0;                                     //Velocidade de rotação

int maingame(){

    SDL_Init(SDL_INIT_EVERYTHING);


    SDL_Window* window = SDL_CreateWindow(
        "Tank Game", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        800, 800, 
        SDL_WINDOW_SHOWN
        );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 9, 20, 33, 255);              //renderizador

    SDL_Surface* surface = SDL_LoadBMP("images/hello_world.bmp"); //criação de superficie
    SDL_Texture* player = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    //Modificações da imagem
    SDL_Rect rect;
    rect.x = 20;                                                  //posição x
    rect.y = 20;                                                  //posição y
    rect.w = surface->w;                                          //largura
    rect.h = surface-> h;                                         //altura


    //rotação
    double angle;
    Uint32 startTime = SDL_GetTicks();                             //tempo inicial

    while(true){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                exit(0);
            }else if(event.type == SDL_MOUSEBUTTONDOWN){
                rect.x +=20;
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        double deltaTime = (currentTime - startTime) / 1000.0; // Converter para segundos
        double rotationAmout = ROTATION_SPEED * deltaTime;
        angle = rotationAmout;

        SDL_RenderClear(renderer);
        SDL_RenderCopyEx(renderer, player, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);

        angle +=1.0;
        if(angle >=360.0)
        {
            angle -=360.0;
        }

        SDL_Delay(10);
    }

    SDL_DestroyTexture(player);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit;
    return 0;
}