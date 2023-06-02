#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <stdio.h>

const double ROTATION_SPEED = 90.0;         //Velocidade de rotação
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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);             

    //superficie e textura de imagem
    SDL_Surface* surface = SDL_LoadBMP("images/player01.bmp");        
    SDL_Texture* player = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    //Modificações da imagem
    SDL_Rect rect;
    rect.x = 500;            //posição x
    rect.y = 400;            //posição y
    rect.w = surface->w;    //largura
    rect.h = surface-> h;   //altura


    double angle;                                  //angulo de rotação
    Uint32 startTime = SDL_GetTicks();             //tempo inicial

    while(true){
        SDL_Event event;
        while(SDL_PollEvent(&event)){             //identificar e reagir aos eventos
            if(event.type == SDL_QUIT)            //sair do SDL
            {            
                exit(0);
            }
            if(event.type == SDL_KEYDOWN){       //botões de movimento (A,S,D,W)
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

        Uint32 currentTime = SDL_GetTicks();

        if( rect.x < 0)
        {
        std::cout << "bateu borda esqueda" << std::endl;   
        }else if( rect.x + 100 > WINDOW_WIDTH)              //+100 devido ao comprimento da imagem
        {
         std::cout << "bateu borda direita" << std::endl;   
        }
        if( rect.y < 0)
        {
         std::cout << "bateu borda superior" << std::endl;   
        }else if(rect.y + 100 > WINDOW_HEIGHT)              ////+100 devido ao comprimento da imagem
        {
         std::cout << "bateu borda inferior" << std::endl;   
        }

        //Função de rotação
        double deltaTime = (currentTime - startTime) / 1000.0;  // Converter para segundos
        double rotationAmout = ROTATION_SPEED * deltaTime;
        angle = rotationAmout;

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, player, NULL, &rect);
        SDL_RenderPresent(renderer);

        angle +=1.0;         //Rotação modificavel
        if(angle >=360.0)
        {
            angle -=360.0;
        }

        SDL_Delay(10);
    }

    SDL_DestroyTexture(player);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit;                 //fim

    return 0;
}