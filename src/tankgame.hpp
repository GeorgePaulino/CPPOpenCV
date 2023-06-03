#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <stdio.h>

const int WINDOW_WIDTH = 800;              //largura janela
const int WINDOW_HEIGHT = 800;              //altura janela


class Player{
    
};

int maingame(){

    SDL_Init(SDL_INIT_EVERYTHING);         //inicializa SDL


    //Cria janela
    SDL_Window* window = SDL_CreateWindow(
        "Tank Game", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH, WINDOW_HEIGHT, 
        SDL_WINDOW_SHOWN
        );
    
    //renderizador
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);


    //superficie e textura de imagem
    SDL_Surface* surface = SDL_LoadBMP("images/player01.bmp");        
    SDL_Texture* player = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);    
    SDL_FreeSurface(surface);

    //Modificações da imagem
    SDL_Rect rect;
    rect.x = 500;            //posição x
    rect.y = 400;            //posição y
    rect.w = 100;            //largura
    rect.h = 100;            //altura

    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;

    double angle = 0.0;

    while(true){
        SDL_Event event;

        while(SDL_PollEvent(&event)){              //identificar e reagir aos eventos
            if(event.type == SDL_QUIT)             //sair do SDL
            {            
                exit(0);
            }
            if(event.type == SDL_KEYDOWN){         //botões de movimento (A,S,D,W)
                SDL_Keycode key = event.key.keysym.sym;
                if( key == SDLK_a )
                {
                    moveLeft = true;
                    moveRight = false;
                    moveUp = false;
                    moveDown = false;
                }
                if( key == SDLK_d )
                {
                    moveLeft = false;
                    moveRight = true;
                    moveUp = false;
                    moveDown = false;
                }
                if( key == SDLK_w )
                {
                    moveLeft = false;
                    moveRight = false;
                    moveUp = true;
                    moveDown = false;
                }
                if( key == SDLK_s )
                {
                    moveLeft = false;
                    moveRight = false;
                    moveUp = false;
                    moveDown = true;
                }
            }
        } 

    //movimento continuo
    if (moveLeft) {
        rect.x -= 5;
        angle = 0.0;
    }
    if (moveRight) {
        rect.x += 5;
        angle = 180.0;
    }
    if (moveUp) {
        rect.y -= 5;
        angle = 90.0;
    }
    if (moveDown) {
        rect.y += 5;
        angle = -90.0;
    }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);    
        SDL_RenderClear(renderer);


        //deteca colisoẽs
        if( rect.x < 0)
        {
        std::cout << "bateu borda esqueda" << std::endl; 
        moveLeft = false; 
        }
        else if( rect.x + 100 > WINDOW_WIDTH)              //+w devido ao comprimento da imagem
        {
         std::cout << "bateu borda direita" << std::endl;  
         moveRight = false; 
        }
        if( rect.y < 0)
        {
         std::cout << "bateu borda superior" << std::endl;   
         moveUp = false;
        }
        else if(rect.y + 100 > WINDOW_HEIGHT)              //+h devido ao comprimento da imagem
        {
         std::cout << "bateu borda inferior" << std::endl; 
        moveDown = false;
        }


        SDL_RenderClear(renderer);
        SDL_RenderCopyEx(renderer, player, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);

        SDL_Delay(25);                                     //tempo de renderização
    }

    SDL_DestroyTexture(player);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit;                                              //fim

    return 0;
}