#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <stdio.h>

const int WINDOW_WIDTH = 1000;              //largura janela
const int WINDOW_HEIGHT = 800;              //altura janela

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
    /*SDL_Surface* surface = SDL_LoadBMP("images/player01.bmp");        
    SDL_Texture* player = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);    
    SDL_FreeSurface(surface);*/

    //Modificações da imagem
    SDL_Rect rect;
    rect.x = 500;            //posição x
    rect.y = 400;            //posição y
    rect.w = 100;            //largura
    rect.h = 100;            //altura


    SDL_Rect rect2;
    rect.x = 100;            //posição x
    rect.y = 100;            //posição y
    rect.w = 50;     //largura
    rect.h = 50;    //altura

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
                    rect.x -=10;
                }
                if( key == SDLK_d )
                {
                    rect.x +=10;
                }
                if( key == SDLK_w )
                {
                    rect.y -= 10;
                }
                if( key == SDLK_s )
                {
                    rect.y += 10;
                }
            }
        } 
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);

        //deteca colisoẽs
        if( rect.x < 0)
        {
        std::cout << "bateu borda esqueda" << std::endl;  
        }
        else if( rect.x + 50 > WINDOW_WIDTH)              //+w devido ao comprimento da imagem
        {
         std::cout << "bateu borda direita" << std::endl;   
        }
        if( rect.y < 0)
        {
         std::cout << "bateu borda superior" << std::endl;   
        }
        else if(rect.y + 50 > WINDOW_HEIGHT)              //+h devido ao comprimento da imagem
        {
         std::cout << "bateu borda inferior" << std::endl;   
        }


        /*SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, player, NULL, &rect2);
        SDL_RenderPresent(renderer);*/

        SDL_Delay(1);
    }

    /*SDL_DestroyTexture(player);*/
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit;                 //fim

    return 0;
}